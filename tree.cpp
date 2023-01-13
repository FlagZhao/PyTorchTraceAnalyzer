#include "util/tree.h"

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include <algorithm>
#include <fstream>

using namespace rapidjson;

Tree::Tree()
{
}

Tree::~Tree()
{
}

template <typename T>
std::string stringify(const T &o)
{
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    o.Accept(writer);
    return sb.GetString();
}

void Tree::build(const std::string &data)
{
    Document d;
    d.Parse(data.c_str());
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    auto traces = d.FindMember("traceEvents");
    int string_id = 0;

    for (const Value &iter_trace : traces->value.GetArray())
    {
        auto ph_pair = iter_trace.FindMember("ph");
        auto ph = ph_pair->value.GetString();
        if (std::string(ph) != "X")
        {
            continue;
        }

        auto name_pair = iter_trace.FindMember("name");
        auto name = name_pair->value.GetString();

        auto cat_pair = iter_trace.FindMember("cat");
        auto cat = cat_pair->value.GetString();

        auto pid_pair = iter_trace.FindMember("pid");
        auto pid = pid_pair->value.GetType() == kNumberType
                       ? pid_pair->value.GetInt()
                       : -1;

        auto tid_pair = iter_trace.FindMember("tid");
        auto tid = tid_pair->value.GetType() == kNumberType
                       ? tid_pair->value.GetInt()
                       : -1;

        auto timestamp_pair = iter_trace.FindMember("ts");
        auto timestamp = timestamp_pair->value.GetInt64();

        auto duration_pair = iter_trace.FindMember("dur");
        auto duration = duration_pair->value.GetInt();

        auto args_pair = iter_trace.FindMember("args");
        auto args = stringify<>(args_pair->value);

        int cat_id = string_id++;
        string_table.push_back(cat);
        int name_id = string_id++;
        string_table.push_back(name);
        int args_id = string_id++;
        string_table.push_back(args);

        Event event(cat_id, name_id, pid, tid, timestamp, duration, args_id);

        event_list.push_back(event);
    }
    printf("size of event list is %zu\n", event_list.size());

    std::sort(event_list.begin(), event_list.end());

    start_time = event_list.begin()->timestamp;
    printf("start time: %" PRIi64 "\n", start_time);

    int eventid = 0;
    int64_t lasttimestamp = 0;
    for (Event &i : event_list)
    {
        if (i.timestamp >= lasttimestamp)
        {
            lasttimestamp = i.timestamp;
        }
        else
        {
            printf("Unordered\n");
            return;
        }
        i.event_id = eventid++;
    }
    printf("total event num is %d\n", eventid);

    std::vector<Event> event_stack;
    for (Event &i : event_list)
    {
        if (event_stack.size() == 0)
        {
            event_stack.push_back(i);
        }
        else
        {
            auto tail = event_stack.end() - 1;
            while (tail->timestamp + tail->duration < i.timestamp + i.duration &&
                   event_stack.size() > 0)
            {
                event_stack.pop_back();
                tail = event_stack.end() - 1;
            }

            i.parent_id = tail->event_id;
            event_stack.push_back(i);
        }
    }
}

void Tree::print()
{
    for (const Event &event : event_list)
    {
        printf("%5d | parent: %5d | time: %" PRIi64 " + %d | %s",
               event.event_id,
               event.parent_id,
               event.timestamp - start_time,
               event.duration,
               string_table[event.name].c_str());
        // int temp_parent = event.parent_id;
        // while (temp_parent != -1)
        // {
        //     std::string func_name = string_table[event_list[temp_parent].name];
        //     printf(" | %s", func_name.c_str());
        //     temp_parent = event_list[temp_parent].parent_id;
        // }
        printf("\n");
    }
}

void Tree::buildFromFile(const std::string &path)
{
    std::string data;
    std::ifstream ifile(path, std::ios::in);
    std::getline(ifile, data, '\0');
    this->build(data);
}
