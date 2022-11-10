#include <vector>

struct DoubleAbstractStack {
    // some code goes here
public:
    bool push(double next_element) {
        // some code goes here
        before_push();
        // push code
        after_push(next_element);
        return true;
    }

    // other public methods
protected:
    virtual void before_push() = 0;
    virtual void after_push(double pushed_element) = 0;
    virtual void before_pop() = 0;
    virtual void after_pop(double popped_element) = 0;
};

class DoubleStackWithMin : public DoubleAbstractStack {
public:
    DoubleStackWithMin(): DoubleAbstractStack() {  }
private:
    std::vector<double> minimum_stack;

    void before_push() override {
        return;
    }

    void before_pop() override {
        return;
    }
    
    void after_push(double pushed_element) override {
        double push_element;
        if (minimum_stack.empty())
            push_element = pushed_element;
        else if (pushed_element < minimum_stack.back())
            push_element = pushed_element;
        else
            push_element = minimum_stack.back();

        minimum_stack.push_back(push_element);
    }
    
    void after_pop(double popped_element) override {
        minimum_stack.pop_back();
    }
public:
    double get_min() const {
        return minimum_stack.back();
    }
};
