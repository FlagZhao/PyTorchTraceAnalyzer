class event
{
private:
    /* data */
public:
    int ph;
    int cat;
    int name;
    int pid;
    int tid;
    unsigned long long timestamp;
    unsigned long long duration;
    int args_id;
    int stack_id;
    int parent_id;
    int event_id;
    event(int ph, int cat, int name, int pid, int tid, unsigned long long timestamp, unsigned long long duration,int args_id,int stack_id);
    ~event();
    // event operater>(const event& a, const event& b){
    //     return a.timestamp>b.timestamp;
    // };
};

event::event(int ph, int cat, int name, int pid, int tid, unsigned long long timestamp, unsigned long long duration,int args_id,int stack_id)
{
    this->ph=ph;
    this->cat=cat;
    this->name=name;
    this->pid=pid;
    this->tid=tid;
    this->timestamp=timestamp;
    this->duration=duration;
    this->args_id=args_id;
    this->stack_id=stack_id;
    this->parent_id=-1;
    this->event_id=0;
}

event::~event()
{
}
