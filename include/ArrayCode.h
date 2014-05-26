#ifndef ARRAYCODE_H_INCLUDED
#define ARRAYCODE_H_INCLUDED

class ArrayCode
{
public:
    ArrayCode()
    {

    }
    ~ArrayCode()
    {

    }
    void init() {
        output();
    }
    static void output() {
        tt++;
    }

private:
    static int tt;

};


#endif // ARRAYCODE_H_INCLUDED
