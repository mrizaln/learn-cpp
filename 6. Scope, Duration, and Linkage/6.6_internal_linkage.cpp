/*
    global variable and functions identifiers can have either   internal linkage   or   external linkage.
    an identifier with   internal linkage   can be seen and used within a single file,
    but it is not accessible from other files.
    this means that if two files have identically named identifiers with internal linkage,
    those identifiers will be trated as independent.
*/

//========[ global variables with internal linkage ]========
// global variables with internal linkage are sometimes called internal variables
// to make a non-constant global variavle internal, we use the   static   keyword

static int g_x;             // non-constant globals have external linkage by default, but can be given internal linkage via the static keyword
const int g_y { 1 };        // const globals have internal linkage by default
constexpr int g_z { 2 };    // constexpr globals have internal linkage by default



//========[ functions with internal linkage ]========
// because linkage is a property of an identifier, function identifiers have the same
// linkage property that variable identifier do.
// functions default to external linkage, but can be set to internal linkage via the   static   keyword

static int add(int x, int y)
{
    return x + y;
}