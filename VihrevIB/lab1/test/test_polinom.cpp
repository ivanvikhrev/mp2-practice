#include "gtest.h"
#include "polinom.h"
#include <vector>

//тесты для мономов и полиномов
using std::vector;

string Expr[] = {"0", "xyz","zxy","yzx","x","y","z","x^2","y^2","z^2", "x^2yz", "x+y", "x-y", "x^2-y^2","xyz+xyz","x^2y^2z^2"};
Monom M[] = { Monom() ,Monom(1, 111),Monom(1, 111),Monom(1, 111), Monom(1, 100),Monom(1, 10),Monom(1, 1), Monom(1, 200),Monom(1, 20),Monom(1, 2),Monom(1, 211) };
//............................................................................
TEST(Monom, can_create_monom)
{
	ASSERT_NO_THROW(Monom M);
}
//............................................................................

TEST(Polinom, can_create_polinom)
{
	ASSERT_NO_THROW(Polinom p);
}
//............................................................................
TEST(Polinom, can_copy_polinoms)
{
	Polinom a("x^5");
	ASSERT_NO_THROW(Polinom b(a));
}
//............................................................................
class PolTestParse
{   
	public:
	
	string Line;
	Polinom res;

	PolTestParse(string str , vector<Monom> &M )
	{
		Line = str;
		Rlist<Monom> temp;
		for (int i = 0; i < M.size(); i++)
			temp.OrderedInsert(M[i]);
		res = Polinom(temp);
	}
};
//............................................................................
class TestParsing : public ::testing::TestWithParam< PolTestParse>
{
protected: 
	Polinom P1;
public:
	TestParsing() : P1(GetParam().Line) {}
	~TestParsing() {}
};
//............................................................................
TEST_P(TestParsing, test_polinom_parsing)
{
	EXPECT_EQ(GetParam().res, P1);
}
//............................................................................
INSTANTIATE_TEST_CASE_P(FIRST, TestParsing,::testing::Values(
	 PolTestParse(Expr[0], vector<Monom> {M[0]}),
	 PolTestParse(Expr[1], vector<Monom> {M[1]}),
	 PolTestParse(Expr[2], vector<Monom> {M[2]}),
	 PolTestParse(Expr[3], vector<Monom> {M[3]}),
	 PolTestParse(Expr[4], vector<Monom> {M[4]}),
	 PolTestParse(Expr[5], vector<Monom> {M[5]}),
	 PolTestParse(Expr[6], vector<Monom> {M[6]}),
	 PolTestParse(Expr[7], vector<Monom> {M[7]}),
	 PolTestParse(Expr[8], vector<Monom> {M[8]}),
	 PolTestParse(Expr[9], vector<Monom> {M[9]}),
	 PolTestParse(Expr[10], vector<Monom> {M[10]}),
	 PolTestParse(Expr[11], vector<Monom> {M[4], M[5]}),
	 PolTestParse(Expr[12], vector<Monom> {Monom(1,100),Monom(-1,10)}),
	 PolTestParse(Expr[13], vector<Monom> {Monom(1, 200), Monom(-1, 20)}),
	 PolTestParse(Expr[14], vector<Monom> {Monom(2, 111)}),
	 PolTestParse(Expr[15], vector<Monom> {Monom(1,222)})
));

//............................................................................
class TGeneralPol
{
	public:
	string P1,P2, res;
	TGeneralPol(string RES, string POL1, string POL2)
	{
		P1 = POL1;
		P2 = POL2;
		res = RES;
	}
};
//............................................................................

class TestSum : public ::testing::TestWithParam<TGeneralPol>
{
	public:
		Polinom pol1, pol2, Res;
		TestSum() : pol1(GetParam().P1), pol2(GetParam().P2), Res(GetParam().res) {};
		~TestSum() {};
};
//............................................................................

TEST_P(TestSum, sum)
{
	EXPECT_EQ(Res, pol1 + pol2);
}
//............................................................................

INSTANTIATE_TEST_CASE_P(SECOND, TestSum, ::testing::Values(
	TGeneralPol("0", "1", "-1"),
	TGeneralPol("0", "x", "-x"),
	TGeneralPol("0", "-xyz", "xyz"),
	TGeneralPol("2xyz", "yzx", "xyz"),
	TGeneralPol("x+y", "x", "y"),
	TGeneralPol("3.14x","3x","0.14x"),
	TGeneralPol("18x^2y^2", "10x^2y^2+x^2", "8x^2y^2-x^2")
	));
//............................................................................


class TestMult: public ::testing::TestWithParam<TGeneralPol>
{
	public:
	Polinom pol1, pol2, Res;

	 TestMult() : pol1(GetParam().P1), pol2(GetParam().P2), Res(GetParam().res) {}
	~ TestMult() {}
};

TEST_P(TestMult, mult)
{
	EXPECT_EQ(Res, pol1 * pol2);
}

INSTANTIATE_TEST_CASE_P(THIRD, TestMult, ::testing::Values(
	TGeneralPol("2", "2", "1"),
	TGeneralPol("xyz", "xyz", "1"),
	TGeneralPol("xyz^2", "xz", "zy"),
	TGeneralPol("100x^2", "50x", "2x"),
	TGeneralPol("111xyz", "55.5xy", "2z"),
	TGeneralPol("x+y+z", "1", "x+y+z"),
	TGeneralPol("x^2-y^2", "x-y", "x+y"),
	TGeneralPol("x^3+y^3", "x+y", "y^2-xy+x^2"),
	TGeneralPol("x^3-y^3", "x-y", "y^2+xy+x^2")
));
