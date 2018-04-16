#include <gtest.h>
#include "node.h"
#include "list.h"

//тесты для циклического списка с головой
//............................................................................
TEST(Node, can_create_node)
{
	ASSERT_NO_THROW(Node<double> N);
}
//............................................................................
TEST(Rlist, can_create_Rlist)
{
	ASSERT_NO_THROW(Rlist<double> L);
}
//............................................................................
class EmptyRlist : public testing::Test
{
protected:
	Rlist<int> L;
public:
	EmptyRlist() {};
	~EmptyRlist() {};
};
//............................................................................
TEST_F(EmptyRlist, new_list_is_empty)
{
	EXPECT_EQ(NULL, L.GetCurr()->data);
}
//............................................................................
TEST_F(EmptyRlist, can_copy_empty_list)
{
	ASSERT_NO_THROW(Rlist<int> L2(L));
}
//............................................................................
TEST_F(EmptyRlist, copied_empty_list_is_correct)
{
	Rlist<int> L2(L);
	EXPECT_EQ(NULL, L2.GetCurr()->data);
}
//............................................................................
TEST_F(EmptyRlist, two_empty_lists_are_eq)
{
	Rlist<int> L2;
	EXPECT_EQ(true, L == L2);
}
//............................................................................
TEST_F(EmptyRlist, can_assign_two_empty_lists)
{
	Rlist<int> L2;
	ASSERT_NO_THROW(L = L2);
}
//............................................................................
TEST_F(EmptyRlist, can_assign_empty_list_to_itself)
{
	ASSERT_NO_THROW(L = L);
}
//............................................................................
TEST_F(EmptyRlist, can_clean_empty_list)
{
	ASSERT_NO_THROW(L.Clean());
}

//............................................................................
TEST_F(EmptyRlist, clean_empty_list_is_correct)
{
	L.Clean();
	EXPECT_EQ(NULL, L.GetCurr()->data);
}
//............................................................................
TEST_F(EmptyRlist, can_get_current_from_empty_list)
{
	ASSERT_NO_THROW(L.GetCurr());
}
//............................................................................
TEST_F(EmptyRlist, can_reset_empty_list)
{
	ASSERT_NO_THROW(L.Reset());
}
//............................................................................
TEST_F(EmptyRlist, reset_empty_list_is_correct)
{	
	L.Reset();
	EXPECT_EQ(NULL, L.GetCurr()->data);
}
//............................................................................
TEST_F(EmptyRlist, is_end_is_correct)
{
	EXPECT_EQ(true, L.IsEnd());
}
//............................................................................
TEST_F(EmptyRlist, can_set_next_empty_list)
{
	ASSERT_NO_THROW(L.SetNext());
}
//............................................................................
TEST_F(EmptyRlist, can_insert_after_in_empty_list)
{	
	L.Reset();
	ASSERT_NO_THROW(L.InsertAfter(L.GetCurr(), 1));

}
//............................................................................
TEST_F(EmptyRlist, insert_after_in_empty_list_is_correct)
{	
	L.Reset();
	L.InsertAfter(L.GetCurr(), 1);
	L.Reset();
	int tmp = L.GetCurr()->data;
	EXPECT_EQ(1, tmp);
}
//............................................................................
class FilledRlist : public testing::Test
{
protected:
	Rlist<int> L;
public:
	FilledRlist()
	{	
		for(int i = 0; i<3; i++)
		L.OrderedInsert(i);
	};
	~FilledRlist() {};
};
//............................................................................
TEST_F(FilledRlist, can_copy_filled_list)
{
	ASSERT_NO_THROW(Rlist<int> A(L));
}
//............................................................................
TEST_F(FilledRlist, copied_filled_list_is_correct)
{ 
	Rlist<int> A(L);
	A.Reset();
	EXPECT_EQ(2, A.GetCurr()->data);
	EXPECT_EQ(1, A.GetCurr()->next->data);
	EXPECT_EQ(0, A.GetCurr()->next->next->data);
	EXPECT_NE(L.GetCurr(), A.GetCurr());
}
//............................................................................
TEST_F(FilledRlist, can_assign_filled_list)
{
	ASSERT_NO_THROW(Rlist<int> A = L);
}
//............................................................................
TEST_F(FilledRlist, assigned_filled_list_is_correct)
{
	Rlist<int> A = L;
	A.Reset();
	L.Reset();
	EXPECT_EQ(2, A.GetCurr()->data);
	EXPECT_EQ(1, A.GetCurr()->next->data);
	EXPECT_EQ(0, A.GetCurr()->next->next->data);
	EXPECT_NE(L.GetCurr(), A.GetCurr());
}
//............................................................................