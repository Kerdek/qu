
std::string parse_primary_expression(
    const char *&caret)
{
    std::string result;
    for(;*caret != ' '; ++caret)
    {
        result.push_back(*caret);
    }
    return result;
}