#include "common.h"

void initconfig()
{
    std::ofstream file;

    file.open("test.toml");
    file << "name = \"hello\" " << std::endl;
    file << "id = 188 " << std::endl;
    file << "booltrue = true " << std::endl;
    file << "boolfalse = false " << std::endl;
    file << "[section]" << std::endl;
    file << "name = \"hello\" " << std::endl;
    file << "id = 188 " << std::endl;
    file << "booltrue = true " << std::endl;
    file << "[section.physical]" << std::endl;
    file << "name = \"hello\" " << std::endl;
    file << "id = 188 " << std::endl;
    file << "booltrue = true " << std::endl;
    file.close();
}

TEST(TOML, get)
{
    Result r;

    initconfig();

    sptr<IApplication> spApp;

    r = uapCreateApplication(spApp.getaddrof());
    EXPECT_EQ(r, R_SUCCESS);

    sptr<IToml> spConfig;
    r = spApp->createInstance(IID_ITOML, (void **)&spConfig);
    EXPECT_EQ(r, R_SUCCESS);

    r = spConfig->initialize(spApp.get(), "test.toml");
    EXPECT_EQ(r, R_SUCCESS);

    char *s=new char[8];
    Ulong *actureLength= new Ulong();
    r = spConfig->getString("name", s,8,actureLength);
    EXPECT_EQ(r, R_SUCCESS);
    std::string PStr=s;
    EXPECT_EQ(PStr, "hello");
    delete[] s;
    
    char *string=new char[8];
    r = spConfig->getString("section","name", string,8,actureLength);
    EXPECT_EQ(r, R_SUCCESS);
    PStr=string;
    EXPECT_EQ(PStr, "hello");
    delete string;

    char *stringss=new char[8];
    r = spConfig->getString("section","physical","name", stringss,8,actureLength);
    EXPECT_EQ(r, R_SUCCESS);
    PStr=stringss;
    EXPECT_EQ(PStr, "hello");
    delete stringss;
    delete actureLength;

    bool b;
    r = spConfig->getBool("booltrue", b);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(b, true);

    r = spConfig->getBool("boolfalse", b);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(b, false);
    
    r = spConfig->getBool("section","booltrue", b);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(b, true);
    
    b=false;
    r = spConfig->getBool("section","physical","booltrue", b);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(b, true);

    int i;
    r = spConfig->getInt("id", i);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(i, 188);
    
    i=0;
    r = spConfig->getInt("section","id", i);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(i, 188);

    i=0;
    r = spConfig->getInt("section","physical","id", i);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(i, 188);
}

TEST(TOML, set)
{
    Result r;

    initconfig();

    sptr<IApplication> spApp;

    r = uapCreateApplication(spApp.getaddrof());
    EXPECT_EQ(r, R_SUCCESS);

    sptr<IToml> spConfig;
    r = spApp->createInstance(IID_ITOML, (void **)&spConfig);
    EXPECT_EQ(r, R_SUCCESS);

    r = spConfig->initialize(spApp.get(), "test.toml");
    EXPECT_EQ(r, R_SUCCESS);

    int si=18;
    r = spConfig->setInt("id", si);
    EXPECT_EQ(r, R_SUCCESS);

    r = spConfig->setInt("section","id", si);
    EXPECT_EQ(r, R_SUCCESS);

    r = spConfig->setInt("section","physical","id", si);
    EXPECT_EQ(r, R_SUCCESS);

    int i;
    r = spConfig->getInt("id", i);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(i, 18);

    r = spConfig->getInt("section","id", i);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(i, 18);

    r = spConfig->getInt("section","physical","id", i);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(i, 18);

    bool sb=false;
    r = spConfig->setBool("booltrue", sb);
    EXPECT_EQ(r, R_SUCCESS);

    r = spConfig->setBool("section","booltrue", sb);
    EXPECT_EQ(r, R_SUCCESS);

    r = spConfig->setBool("section","physical","booltrue", sb);
    EXPECT_EQ(r, R_SUCCESS);

    bool b;
    r = spConfig->getBool("booltrue", b);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(b, false);

    r = spConfig->getBool("section","booltrue", b);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(b, false);

    r = spConfig->getBool("section","physical","booltrue", b);
    EXPECT_EQ(r, R_SUCCESS);
    EXPECT_EQ(b, false);

    std::string ss="welcome";
    r = spConfig->setString("name","welcome",7);
    EXPECT_EQ(r, R_SUCCESS);


    r = spConfig->setString("section","name", "welcometwo",11);
    EXPECT_EQ(r, R_SUCCESS);

    r = spConfig->setString("section","physical","name", "welcomethree",13);
    EXPECT_EQ(r, R_SUCCESS);

    std::string s;

    char *v=new char[8];
    Ulong *actureLength= new Ulong();
    r = spConfig->getString("name", v,8,actureLength);
    EXPECT_EQ(r, R_SUCCESS);
    std::string PStr=v;
    EXPECT_EQ(PStr, "welcome");
    delete[] v;

    char *string=new char[11];
    r = spConfig->getString("section","name", string, 11,actureLength);
    EXPECT_EQ(r, R_SUCCESS);
    PStr=string;
    EXPECT_EQ(PStr, "welcometwo");
    delete[] string;

    char *stringss=new char[13];
    r = spConfig->getString("section","physical","name", stringss,13,actureLength);
    EXPECT_EQ(r, R_SUCCESS);
    PStr=stringss;
    EXPECT_EQ(PStr, "welcomethree");
    delete stringss;
    delete actureLength;
}