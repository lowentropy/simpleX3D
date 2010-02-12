TEST(DynamicFields, CreateFieldByNameShouldMakeCorrectType) {
    X3DField* field;
    EXPECT_EQ(X3DField::SFBOOL, (field = X3DField::create("SFBool"))->getType());
    delete field;
    EXPECT_EQ(X3DField::SFVEC3D, (field = X3DField::create("SFVec3d"))->getType());
    delete field;
    EXPECT_EQ(X3DField::MFSTRING, (field = X3DField::create("MFStringArray"))->getType());
    delete field;
    EXPECT_EQ(X3DField::SFNODE, (field = X3DField::create("SFNode"))->getType());
    delete field;
    EXPECT_EQ(X3DField::MFNODE, (field = X3DField::create("MFNodeSet"))->getType());
    delete field;
}

TEST(DynamicFields, CreateBadFieldNameShouldThrowError) {
    EXPECT_ANY_THROW(X3DField::create("SFBoolean"));
}
