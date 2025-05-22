#ifndef OBSERVER
#define OBSERVER

class Observer {
public:
    virtual ~Observer() = default;
    virtual void update() = 0;
};

class Observable {
public:
    virtual ~Observable() = default;
    virtual void addObserver(class Observer* observer) = 0;
    virtual void removeObserver(class Observer* observer) = 0;
    virtual void notifyObservers() = 0;
};

#endif // !OBSERVER