#include <string>

struct Animal {
    virtual ~Animal() = default;
    virtual void show() const = 0;
    int n_times = 1;
};

struct Dog : public Animal {
    void show() const override;
    virtual std::string bark() const;
};

struct Cat : public Animal {
    void show() const override;
    virtual std::string bark() const;
};

struct Elephant : public Animal {
    void show() const override;
    virtual std::string bark() const;
};
