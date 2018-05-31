#include "ord_table.h"
#include <gtest.h>


//Тесты для упорядоченной таблицы 
//............................................................
TEST(OrdTable, can_create_ord_table)
{
	ASSERT_NO_THROW(OrdTable<int> Tab);
}
//............................................................
class EmptyOTable : public testing::Test
{
protected:
	OrdTable<int> Tab;
public:
	EmptyOTable() {};
	~EmptyOTable() {};
};
//............................................................
TEST_F(EmptyOTable, new_table_is_empty)
{
	EXPECT_EQ(true, Tab.IsEmpty());
}
////............................................................................
TEST_F(EmptyOTable, can_copy_empty_table)
{
	ASSERT_NO_THROW(OrdTable<int> T(Tab));
}
////............................................................................
TEST_F(EmptyOTable, copied_empty_table_is_correct)
{
	OrdTable<int> T(Tab);
	EXPECT_EQ(Tab.IsEmpty(), T.IsEmpty());
}
////............................................................................
TEST_F(EmptyOTable, cant_get_current_from_empty_table)
{
	ASSERT_ANY_THROW(Tab.GetCurr());
}
////............................................................................
TEST_F(EmptyOTable, can_reset_empty_table)
{
	ASSERT_NO_THROW(Tab.Reset());
}
////............................................................................
TEST_F(EmptyOTable, reset_empty_table_is_correct)
{
	Tab.Reset();
	ASSERT_ANY_THROW(Tab.GetCurr());
}
////............................................................................
TEST_F(EmptyOTable, is_end_is_correct_for_empty_table)
{
	bool k = Tab.IsTabEnded();
	EXPECT_EQ(true, Tab.IsTabEnded());
}
////............................................................................
TEST_F(EmptyOTable, cant_set_next_empty_table)
{
	ASSERT_ANY_THROW(Tab.SetNext());
}
////............................................................................
TEST_F(EmptyOTable, cant_delete_from_empty_table)
{
	ASSERT_ANY_THROW(Tab.Delete("one"));
}
////............................................................................
TEST_F(EmptyOTable, cant_search_in_empty_table)
{
	ASSERT_ANY_THROW(Tab.Search("one"));
}
////............................................................................
TEST_F(EmptyOTable, can_insert_in_empty_table)
{
	ASSERT_NO_THROW(Tab.Insert(1, "one"));
}
////----------------------------------------------------------------------------
TEST_F(EmptyOTable, insert_in_empty_table_is_correct)
{
	Tab.Insert(1, "one");
	EXPECT_EQ(1, Tab.GetCurrRecords());
	EXPECT_EQ(1, *(Tab.Search("one")));
}
//----------------------------------------------------------------------------
class FilledOrdTable : public testing::Test
{
protected:
	OrdTable<int> T;
public:
	FilledOrdTable()
	{
		for (int i = 0; i < 3; i++)
			T.Insert(i, std::to_string(i));
	}
	~FilledOrdTable() {};
};
//----------------------------------------------------------------------------
TEST_F(FilledOrdTable, can_get_current_from_filled_table)
{
	T.Reset();
	ASSERT_NO_THROW(*(T.GetCurr()));
}
//----------------------------------------------------------------------------
TEST_F(FilledOrdTable, get_current_from_filled_table_is_corect)
{
	T.Reset();
	EXPECT_EQ(0, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, can_set_next_in_filled_table)
{
	T.Reset();
	ASSERT_NO_THROW(T.SetNext());
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, set_next_in_filled_table_is_correct)
{
	T.Reset();
	T.SetNext();
	EXPECT_EQ(1, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, set_next_in_the_end)
{
	T.Reset();
	T.SetNext();//1
	T.SetNext();//2
	T.SetNext();//
	EXPECT_EQ(0, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, filled_table_was_correctly_filled)
{
	T.Reset();
	EXPECT_EQ(0, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(1, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(2, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, can_copy_filled_table)
{
	ASSERT_NO_THROW(OrdTable<int> A(T));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, copied_filled_table_is_correct)
{
	OrdTable<int> A(T);
	A.Reset();
	EXPECT_EQ(0, *(A.GetCurr()));
	A.SetNext();
	EXPECT_EQ(1, *(A.GetCurr()));
	A.SetNext();
	EXPECT_EQ(2, *(A.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, copied_filled_table_has_its_own_memory)
{
	OrdTable<int> A(T);
	A.Delete("0");
	T.Reset();
	A.Reset();
	EXPECT_EQ(0, *(T.GetCurr()));
	EXPECT_NE(0, *(A.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, is_full_is_correct)
{
	for (int i = 3; i<10; i++)
		T.Insert(i, std::to_string(i));
	EXPECT_EQ(true, T.IsFull());
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, isnt_full_after_realloc)
{
	for (int i = 3; i<11; i++)
		T.Insert(i, std::to_string(i));
	EXPECT_EQ(false, T.IsFull());
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, is_empty_after_deletion)
{
	T.Delete("0");
	T.Delete("1");
	T.Delete("2");
	EXPECT_EQ(true, T.IsEmpty());
}
////---------------------------------------------------------------------------
TEST_F(FilledOrdTable, can_insert_after_deletion)
{
	T.Delete("0");
	T.Delete("1");
	T.Delete("2");
	T.Insert(0, "0");
	EXPECT_EQ(0, *(T.GetCurr()));
}
//// ----------------------------------------------------------------------------
TEST_F(FilledOrdTable, can_insert)
{
	T.Insert(3, "3");
	T.Reset();
	T.SetNext();
	T.SetNext();
	T.SetNext();
	EXPECT_EQ(3, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, can_delete)
{
	T.Delete("2");
	T.Reset();
	EXPECT_EQ(0, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(1, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(0, *(T.GetCurr()));

}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, can_search)
{
	T.Search("2");
	EXPECT_EQ(2, *(T.Search("2")));
}
////----------------------------------------------------------------------------
TEST_F(FilledOrdTable, Ord_Insert_Is_Correct)
{
	T.Insert(5, "5");
	T.Insert(9, "9");
	T.Insert(7, "7");
	T.Insert(4, "4");
	T.Reset();
	EXPECT_EQ(0, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(1, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(2, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(4, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(5, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(7, *(T.GetCurr()));
	T.SetNext();
	EXPECT_EQ(9, *(T.GetCurr()));
}
//----------------------------------------------------------------------------
TEST_F(FilledOrdTable, cant_insert_record_wich_key_isnt_unique)
{
	ASSERT_ANY_THROW(T.Insert(2, "2"));
}