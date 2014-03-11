#include "SimpleTable.h"

int main()
{
    SimpleTable table;
    table.useTitle();
    table.setTitle("test table1");
    table.setTable() 
        ("c1", "c2", "c3")
        ("v1",    1,    2)
        ("v2",    1,    2)
        ;
    table.print();
    return 0;
}