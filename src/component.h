#ifndef COMPONENT_H
#define COMPONENT_H

class Component {
  public:
    virtual void onStart() = 0;
    virtual const bool onUpdate(const double delta) = 0;
    virtual void onDestroy() = 0;
    virtual ~Component() {}
};
#endif