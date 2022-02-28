// ======[ identifier naming rules ]=====
    // 1. The identifier can not be a keyword. Keywords are reserved.
    // 2. The identifier can only be composed of letters (lower or upper case), numbers, and the underscore character.
    //    That means the name can not contain symbols (except the underscore) nor whitespace (spaces or tabs).
    // 3. The identifier must begin with a letter (lower or upper case) or an underscore. It can not start with a number.
    // 4. C++ is case sensitive, and thus distinguishes between lower and upper case letters. nvalue is different than
    //    nValue is different than NVALUE.

    // ======[ best practice ]======
    // 1. it is a convention that identifier should begin with lowercase letter
    // 2. function name usually started with lowercase letter
    // 4. identifier that starts with capital letter typically used for user-defined types
    // 5. if identifier is multi-word: (a) words separated by underscore    snake_case
    //                                 (b) intercapped                      snakeCase
    // 6. avoid naming identifier starting with an underscore (typically reserved)
    // 7. the identifer should make clear what kind of value it holds


// ======[ keywords ]======
// as in C++20, there are 92 reserved words
/*
    alignas
    alignof
    and
    and_eq
    asm
    auto
    bitand
    bitor
    bool
    break
    case
    catch
    char
    char8_t (since C++20)
    char16_t
    char32_t
    class
    compl
    concept (since C++20)
    const
    consteval (since C++20)
    constexpr
    constinit (since C++20)
    const_cast
    continue
    co_await (since C++20)
    co_return (since C++20)
    co_yield (since C++20)
    decltype
    default
    delete
    do
    double
    dynamic_cast
    else
    enum
    explicit
    export
    extern
    false
    float
    for
    friend
    goto
    if
    inline
    int
    long
    mutable
    namespace
    new
    noexcept
    not
    not_eq
    nullptr
    operator
    or
    or_eq
    private
    protected
    public
    register
    reinterpret_cast
    requires (since C++20)
    return
    short
    signed
    sizeof
    static
    static_assert
    static_cast
    struct
    switch
    template
    this
    thread_local
    throw
    true
    try
    typedef
    typeid
    typename
    union
    unsigned
    using
    virtual
    void
    volatile
    wchar_t
    while
    xor
    xor_eq
*/