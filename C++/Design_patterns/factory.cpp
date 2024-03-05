/*简单工厂模式*/
class products {
public:
    int money = 0;
    virtual void sell() = 0;
};
class apple :public products {
public:
    void sell() {
        money += 10;
    }
};
class banana :public products {
public:
    void sell() {
        money += 20;
    }
};
class factory {
public:
    static products* get_product(int d) {
        switch (d) {
        case 0:return new apple;
        case 1:return new banana;
        }
        return nullptr;
    }
};


/*工厂方法模式*/
class products {
public:
    virtual void sell() = 0;
};

class factory {
public:
    virtual products* get_product() = 0;
};

class apple :public products{
public:
    void sell(){
        std::cout << "apple" << std::endl;
    }
};

class banana :public products {
public:
    void sell() {
        std::cout << "banana" << std::endl;
    }
};

class apple_producter:public factory  {
public:
    products* get_product() {
        return new apple;
    }
};

class banana_producter:public factory {
public:
    products* get_product() {
        return new banana;
    }
};

/*抽象工厂模式*/
class products {
public:
    virtual void show() = 0;
};
//抽象产品族
class fruit :public products {};

class apple :public fruit {
public:
    void show() {
        std::cout << "apple" << std::endl;
    }
};

class banana :public fruit {
public:
    void show() {
        std::cout << "banana" << std::endl;
    }
};
//抽象产品族
class vegetable :public products {};

class potato :public vegetable {
public:
    void show() {
        std::cout << "potato" << std::endl;
    }
};

class tomato :public vegetable {
public:
    void show() {
        std::cout << "tomato" << std::endl;
    }
};

class factory {
public:
    virtual fruit* get_fruit() = 0;
    virtual vegetable* get_vegetable() = 0;
};

class farm1:public factory {
public:
    fruit* get_fruit() {
        return new apple;
    }
    vegetable* get_vegetable() {
        return new potato;
    }
};

class farm2:public factory {
public:
    fruit* get_fruit() {
        return new banana;
    }
    vegetable* get_vegetable() {
        return new tomato;
    }
};
