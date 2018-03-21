#include <gtest.h>
#include "list.h"


class TestList : public testing::Test
{
protected:
	Rlist<int> list1;
	Rlist<int> list2;
public:
	TestList()
	{
		list2.OrderedInsert(1);
		list2.OrderedInsert(2);
		list2.OrderedInsert(3);
	};
	~TestList() {};
};

TEST_F(TestList, can_create_list)
{
	ASSERT_NO_THROW(Rlist<int> list);
}

TEST_F(TestList, empty_list_is_working)
{
	EXPECT_EQ(true, list1.IsEnded());
}

TEST_F(TestList, can_copy_empty_list)
{
	ASSERT_NO_THROW(Rlist<int> list(list1));
}

TEST_F(TestList, copied_empty_list_is_correct)
{
	Rlist<int> list(list1);
	EXPECT_EQ(true, list.IsEnded());
	EXPECT_NE(list1.GetCurr(), list.GetCurr());
}

TEST_F(TestList, can_assign_empty_list)
{
	ASSERT_NO_THROW(Rlist<int> list = list1);
}

TEST_F(TestList, assigned_empty_list_is_correct)
{
	Rlist<int> list = list1;
	EXPECT_EQ(true, list.IsEnded());
	EXPECT_NE(list1.GetCurr(), list.GetCurr());
}

TEST_F(TestList, can_insert_in_ordered_empty_list)
{
	ASSERT_NO_THROW(list1.OrderedInsert(5));
}
