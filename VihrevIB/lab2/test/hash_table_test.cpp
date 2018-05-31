#include <gtest.h>
#include "hash_table.h"


//Тесты для хэш таблицы 
//............................................................
TEST(HashTable, can_create_unord_table)
{
	ASSERT_NO_THROW(HashTable<int> Tab);
}
//............................................................
class EmptyHTable : public testing::Test
{
protected:
	HashTable<int> Tab;
public:
	EmptyHTable() {};
	~EmptyHTable() {};
};
////............................................................
TEST_F(EmptyHTable, new_table_is_empty)
{
	EXPECT_EQ(true, Tab.IsEmpty());
}
////............................................................................
TEST_F(EmptyHTable, can_copy_empty_table)
{
	ASSERT_NO_THROW(HashTable<int> T(Tab));
}
////............................................................................
TEST_F(EmptyHTable, copied_empty_table_is_correct)
{
	HashTable<int> T(Tab);
	EXPECT_EQ(Tab.IsEmpty(), T.IsEmpty());
}
////............................................................................
TEST_F(EmptyHTable, cant_get_current_from_empty_table)
{
	ASSERT_ANY_THROW(Tab.GetCurr());
}
////............................................................................
TEST_F(EmptyHTable, can_reset_empty_table)
{
	ASSERT_NO_THROW(Tab.Reset());
}
////............................................................................
TEST_F(EmptyHTable, reset_empty_table_is_correct)
{
	Tab.Reset();
	ASSERT_ANY_THROW(Tab.GetCurr());
}
////............................................................................
//TEST_F(EmptyHTable, is_end_is_correct_for_empty_table)
//{
//	bool k = Tab.IsTabEnded();
//	EXPECT_EQ(true, Tab.IsTabEnded());
//}
////............................................................................
TEST_F(EmptyHTable, cant_set_next_empty_table)
{
	ASSERT_ANY_THROW(Tab.SetNext());
}
////............................................................................
TEST_F(EmptyHTable, cant_delete_from_empty_table)
{
	ASSERT_ANY_THROW(Tab.Delete("one"));
}
////............................................................................
TEST_F(EmptyHTable, cant_search_in_empty_table)
{
	ASSERT_ANY_THROW(Tab.Search("one"));
}
////............................................................................
TEST_F(EmptyHTable, can_insert_in_empty_table)
{
	ASSERT_NO_THROW(Tab.Insert(1, "one"));
}
////----------------------------------------------------------------------------
TEST_F(EmptyHTable, insert_in_empty_table_is_correct)
{
	Tab.Insert(1, "one");
	EXPECT_EQ(1, Tab.GetCurrRecords());
	EXPECT_EQ(1, *(Tab.Search("one")));
}
//----------------------------------------------------------------------------
class FilledHashTable : public testing::Test
{
protected:
	HashTable<int> T;
public:
	FilledHashTable()
	{
		for (int i = 0; i < 3; i++)
			T.Insert(i, std::to_string(i));
	}
	~FilledHashTable() {};
};
//----------------------------------------------------------------------------
TEST_F(FilledHashTable, can_get_current_from_filled_table)
{
	T.Reset();
	ASSERT_NO_THROW(T.GetCurr());
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, get_current_from_filled_table_is_corect)
{
	T.Reset();
	EXPECT_EQ(2, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, can_set_next_in_filled_table)
{
	T.Reset();
	ASSERT_NO_THROW(T.SetNext());
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, set_next_in_filled_table_is_correct)
{
	T.Reset();
	T.SetNext();
	EXPECT_EQ(0, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, set_next_in_the_end)
{
	T.Reset();
	T.SetNext();//0
	T.SetNext();//1
	T.SetNext();//2
	EXPECT_EQ(2, *(T.GetCurr()));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, filled_table_was_correctly_filled)
{
	T.Reset();
	EXPECT_EQ(0, *(T.Search("0")));
	EXPECT_EQ(1, *(T.Search("1")));
	EXPECT_EQ(2, *(T.Search("2")));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, can_copy_filled_table)
{
	ASSERT_NO_THROW(HashTable<int> A(T));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, copied_filled_table_is_correct)
{
	HashTable<int> A(T);
	EXPECT_EQ(0, *(A.Search("0")));
	EXPECT_EQ(1, *(A.Search("1")));
	EXPECT_EQ(2, *(A.Search("2")));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, copied_filled_table_has_its_own_memory)
{
	HashTable<int> A(T);
	A.Delete("0");
	T.Reset();
	A.Reset();
	EXPECT_EQ(0, *(T.Search("0")));
	ASSERT_ANY_THROW(A.Search("0"));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, is_full_is_correct)
{
	for (int i = 3; i<10; i++)
		T.Insert(i, std::to_string(i));
	EXPECT_EQ(true, T.IsFull());
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, isnt_full_after_realloc)
{
	for (int i = 3; i<11; i++)
		T.Insert(i, std::to_string(i));
	EXPECT_EQ(false, T.IsFull());
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, is_empty_after_deletion)
{
	T.Delete("0");
	T.Delete("1");
	T.Delete("2");
	EXPECT_EQ(true, T.IsEmpty());
}
////---------------------------------------------------------------------------
TEST_F(FilledHashTable, can_insert_after_deletion)
{
	T.Delete("0");
	T.Delete("1");
	T.Delete("2");
	T.Insert(0, "0");
	EXPECT_EQ(0, *(T.GetCurr()));
}
//// ----------------------------------------------------------------------------
TEST_F(FilledHashTable, can_insert)
{
	T.Insert(3, "3");
	T.Reset();

	EXPECT_EQ(3, *(T.Search("3")));
}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, can_delete)
{
	T.Delete("2");
	ASSERT_ANY_THROW(T.Search("2"));

}
////----------------------------------------------------------------------------
TEST_F(FilledHashTable, can_search)
{
	T.Search("2");
	EXPECT_EQ(2, *(T.Search("2")));
}
//----------------------------------------------------------------------------
TEST_F(FilledHashTable, cant_insert_record_wich_key_isnt_unique)
{
	ASSERT_ANY_THROW(T.Insert(2, "2"));
}