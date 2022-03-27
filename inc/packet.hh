
#ifndef PACKET_HH
#define PACKET_HH


template <class generic>
class Packet
{
private:

    generic content; //generic will usually be a string
    int priority; //the higher the priority, the sooner the object will be pulled out of the PQ.

public:

    //Do i need to add something here? used in Person::sendMessage()
    Packet() {}

    Packet(generic cntnt, int prty)
    {
        content = cntnt;
        priority = prty;
    }

    Packet(const Packet<generic>& pckt)
    {
        content = pckt.getContent();
        priority = pckt.getPriority();
    }

    inline generic getContent() const { return content; }

    inline int getPriority() const { return priority; }

    inline void setPriority(int p) {priority = p;}
    inline void setContent(generic c) {content = c;}

};

template <class generic>
std::ostream& operator<<(std::ostream& os, const Packet<generic>& pckt)
{
    os << "(" << pckt.getContent() << ", " << pckt.getPriority() << ")";
    return os; 
}

#endif