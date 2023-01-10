#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "./include/util/report.h"

#include <fstream>
#include <sstream>
// #include <ifstream>
#include <vector>
#include <iostream>
// using namespace std;
using namespace rapidjson;

void loadFromFile(const std::string &path, std::string &data)
{
    std::ifstream ifile;
    ifile.open(path, std::ios::in);
    std::ostringstream ostring;
    ostring << ifile.rdbuf();
    data = ostring.str();
}

template <typename T>
std::string stringify(const T &o)
{
    StringBuffer sb;
    Writer<StringBuffer> writer(sb);
    o.Accept(writer);
    return sb.GetString();
}

int main()
{
    printf("Test\n");
    Report *report_pointer = new Report;
    int string_id = 0;
    // int args_id=0;
    std::string path = "a100-test-runner_549810.1668545729102.cu116.pt.trace.json";
    std::string data;
    loadFromFile(path, data);

    Document d;
    d.Parse(data.c_str());
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    auto traces = d.FindMember("traceEvents");
    // auto traces_array=traces->value.GetArray();
    unsigned long long lasttimestamp = 0;

    for (auto &iter_trace : traces->value.GetArray())
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
        auto timestamp = timestamp_pair->value.GetUint64();

        auto duration_pair = iter_trace.FindMember("dur");
        auto duration = duration_pair->value.GetUint64();

        auto args_pair = iter_trace.FindMember("args");
        auto args = stringify<>(args_pair->value);

        if (timestamp > lasttimestamp)
        {
            lasttimestamp = timestamp;
        }

        int ph_id = 0; // unused
        int cat_id = string_id++;
        report_pointer->string_table.push_back(cat);
        int name_id = string_id++;
        report_pointer->string_table.push_back(name);
        int args_id = string_id++;
        report_pointer->string_table.push_back(args);
        int stack_id = 0; // unused
        // int stack_id=string_id++;
        // report_pointer.call_stack.pushback(stack_id);

        Event event(ph_id, cat_id, name_id, pid, tid, timestamp, duration, args_id, stack_id);

        report_pointer->event_list.push_back(event);
    }

    printf("size of event list is %zu\n", report_pointer->event_list.size());
    // std::sort();
    report_pointer->reorder();

    lasttimestamp = 0;
    int eventid = 0;
    for (Event &i : report_pointer->event_list)
    {
        // printf("last is %lld, this is %lld\n",lasttimestamp,i.timestamp);
        if (i.timestamp >= lasttimestamp)
        {
            lasttimestamp = i.timestamp;
        }
        else
        {
            printf("Unordered\n");
            return 0;
        }
        i.event_id = eventid++;
    }
    printf("total event num is %d\n", eventid);

    std::vector<Event> event_stack;
    for (Event &i : report_pointer->event_list)
    {
        if (event_stack.size() == 0)
        {
            event_stack.push_back(i);
            // printf();
            continue;
        }
        else
        {
            auto tail = event_stack.end() - 1;
            while (tail->timestamp + tail->duration < i.timestamp && event_stack.size() > 0)
            {
                event_stack.pop_back();
            }

            if (event_stack.size() == 0)
            {
                event_stack.push_back(i);
                // printf();
                continue;
            }
            else
            {
                i.parent_id = tail->event_id;
                event_stack.push_back(i);
            }
        }
        int temp_parent = i.parent_id;
        // printf("parent id is:%d\n",i.parent_id);
        printf("%d | ", i.event_id);
        printf("parent:%d | ", i.parent_id);
        printf("time:%zu + %zu | ", i.timestamp, i.duration);
        printf("%s | ", report_pointer->string_table[i.name].c_str());
        while (temp_parent != -1)
        {
            std::string func_name = report_pointer->string_table[report_pointer->event_list[temp_parent].name];
            printf("%s | ", func_name.c_str());
            temp_parent = report_pointer->event_list[temp_parent].parent_id;
        }
        printf("\n\n");
    }
}