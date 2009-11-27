TEST(DynamicFields, CreateFieldByNameShouldMakeCorrectType) {
    EXPECT_EQ(X3DField::SFBOOL, X3DField::create("SFBool")->getType());
    EXPECT_EQ(X3DField::SFVEC3D, X3DField::create("SFVec3d")->getType());
    EXPECT_EQ(X3DField::MFSTRING, X3DField::create("MFString")->getType());
    EXPECT_EQ(X3DField::SFNODE, X3DField::create("SFNode")->getType());
    EXPECT_EQ(X3DField::MFNODE, X3DField::create("MFNode")->getType());
}

TEST(DynamicFields, CreateBadFieldNameShouldThrowError) {
    EXPECT_ANY_THROW(X3DField::create("SFBoolean"));
}
