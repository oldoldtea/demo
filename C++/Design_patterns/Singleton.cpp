class A {
	A() {}
	A(const A&) = delete;
	A& operator=(const A&) = delete;
public:
	static A& get_val() {
		static A a;
		return a;
	}
};
