define i32 @ifElseIf() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 5, i32* %2, align 4
  store i32 10, i32* %3, align 4
  %4 = load i32, i32* %2, align 4
  %5 = icmp eq i32 %4, 6
  br i1 %5, label %9, label %6

6:
  %7 = load i32, i32* %3, align 4
  %8 = icmp eq i32 %7, 11
  br i1 %8, label %9, label %11

9:
  %10 = load i32, i32* %2, align 4
  store i32 %10, i32* %1, align 4
  br label %34

11:
  %12 = load i32, i32* %3, align 4
  %13 = icmp eq i32 %12, 10
  br i1 %13, label %14, label %18

14:
  %15 = load i32, i32* %2, align 4
  %16 = icmp eq i32 %15, 1
  br i1 %16, label %17, label %18

17:
  store i32 25, i32* %2, align 4
  br label %31

18:
  %19 = load i32, i32* %3, align 4
  %20 = icmp eq i32 %19, 10
  br i1 %20, label %21, label %27

21:
  %22 = load i32, i32* %2, align 4
  %23 = icmp eq i32 %22, -5
  br i1 %23, label %24, label %27

24:
  %25 = load i32, i32* %2, align 4
  %26 = add nsw i32 %25, 15
  store i32 %26, i32* %2, align 4
  br label %30

27:
  %28 = load i32, i32* %2, align 4
  %29 = sub nsw i32 0, %28
  store i32 %29, i32* %2, align 4
  br label %30

30:
  br label %31

31:
  br label %32

32:
  %33 = load i32, i32* %2, align 4
  store i32 %33, i32* %1, align 4
  br label %34

34:
  %35 = load i32, i32* %1, align 4
  ret i32 %35
}

define i32 @main() {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ifElseIf()
  %3 = call i32 @putint(i32 %2)
  ret i32 0
}
