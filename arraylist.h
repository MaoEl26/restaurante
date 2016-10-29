#ifndef ARRAYLIST_H
#define ARRAYLIST_H

template<class E>
class ArrayList
{
    public:

        ArrayList ();
        ArrayList (int pMaX);
        E getValue();
        int getPos();
        int getSize();
        E remove(int pos);
        void goToStart();
        void goToEnd();
        void goToPos(int pos);
        void previous();
        void next();
        void append (E Element);
        void insert(E pElement);
        void print ();
        E returnPos(int pos);
        void allEqual(E pElement);
        void setValue(int pos,E value);
        //virtual ~ArrayList();
        void clear();
        int getMax();

    protected:

        int size;
        int max;
        int pos;
        E* elements;

};

#endif // ARRAYLIST_H
