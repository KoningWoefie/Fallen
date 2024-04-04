class Component
{
public:
    Component();
    virtual ~Component();

    unsigned int getId() { return id; };
private:
    unsigned int id;
};
