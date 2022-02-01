#include <gtest/gtest.h>

#include <type_traits>

#include <property.hxx>

TEST(Property, links)
{
	property_t<int> p(0);
}

TEST(Property, default_get)
{
	property_t<int> p(5);
	ASSERT_EQ(5, p.get());
}

TEST(Property, implicit_get)
{
	property_t<int> p(5);
	ASSERT_EQ(5, p);
}

TEST(Property, default_set)
{
	property_t<int> p(0);
	p.set(5);
	ASSERT_EQ(5, p.get());
}

TEST(Property, implicit_set)
{
	property_t<int> p(0);
	p = 5;
	ASSERT_EQ(5, p.get());
}

struct CustomGet : default_delegate<int>
{
	int get(int const& lhs) const override
	{
		return lhs + 1;
	}
};

TEST(Property, custom_get)
{
	property_t<int, CustomGet> p(0);
	ASSERT_EQ(1, p.get());
}

struct CustomSet : default_delegate<int>
{
	void set(int& lhs, int const& rhs) override
	{
		lhs = rhs + 1;
	}
};

TEST(Property, custom_set)
{
	property_t<int, CustomSet> p(0);
	ASSERT_EQ(1, p.get());
	p = 2;
	ASSERT_EQ(3, p.get());
}

struct MyContainer
{
	property_t<int> value;
};

TEST(Property, as_data_member)
{
	MyContainer c;
	ASSERT_EQ(0, c.value);
	c.value = 1;
	ASSERT_EQ(1, c.value);
}

struct CustomDelegate : default_delegate<int>
{
	int get(int const& lhs) const override
	{
		return lhs + 1;
	}
	void set(int& lhs, int const& rhs) override
	{
		lhs = rhs + 1;
	}
};

struct MyContainerWithDelegate
{
	property_t<int, CustomDelegate> value;
};

TEST(Property, as_data_member_with_custom_delegate)
{
	MyContainerWithDelegate c;
	ASSERT_EQ(1 /* get() adds 1 */, c.value);
	c.value = 1;
	ASSERT_EQ(3 /* get() and set() both add 1 */, c.value);
}

TEST(Property, get_delegate_default)
{
	MyContainer c;
	const bool is_same_type = std::is_same_v<default_delegate<int>&, decltype(c.value.delegate())>;
	ASSERT_TRUE(is_same_type);
}

TEST(Property, get_delegate_custom)
{
	MyContainerWithDelegate c;
	const bool is_same_type = std::is_same_v<CustomDelegate&, decltype(c.value.delegate())>;
	ASSERT_TRUE(is_same_type);
}

struct MutableDelegate : default_delegate<int>
{
	int get(int const& lhs) const override
	{
		return lhs + offset;
	}
	void set(int& lhs, int const& rhs) override
	{
		lhs = rhs + offset;
	}

	int offset = 0;
};

struct MyContainerWithMutableDelegate
{
	property_t<int, MutableDelegate> value;
};

TEST(Property, get_delegate_custom_instance)
{
	MyContainerWithMutableDelegate c;
	auto& delegate = c.value.delegate();

	ASSERT_EQ(0, delegate.offset);
	ASSERT_EQ(0, c.value);

	delegate.offset = 1;
	ASSERT_EQ(1, c.value);
	c.value = 1;
	ASSERT_EQ(3, c.value);

	delegate.offset = 0;
	ASSERT_EQ(2, c.value);
	c.value = 0;
	ASSERT_EQ(0, c.value);

	delegate.offset = -1;
	ASSERT_EQ(-1, c.value);
	c.value = 1;
	ASSERT_EQ(-1, c.value);
}
