add2 = (a1: int, a2: int) => {
    ret a1 + a2;
}
main = (argc: int, argv: arr<str>): int => {
    out(add2(5 2));
    ret 0;
}