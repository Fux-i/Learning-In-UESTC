define i32 @get_one(i32 %0) {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  ret i32 1
}
define i32 @deepWhileBr(i32 %0, i32 %1) {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %8 = load i32, i32* %3, align 4
  %9 = load i32, i32* %4, align 4
  %10 = add nsw i32 %8, %9
  store i32 %10, i32* %5, align 4
  br label %11

11:
  %12 = load i32, i32* %5, align 4
  %13 = icmp slt i32 %12, 75
  br i1 %13, label %14, label %34

14:
  store i32 42, i32* %6, align 4
  %15 = load i32, i32* %5, align 4
  %16 = icmp slt i32 %15, 100
  br i1 %16, label %17, label %33

17:
  %18 = load i32, i32* %5, align 4
  %19 = load i32, i32* %6, align 4
  %20 = add nsw i32 %18, %19
  store i32 %20, i32* %5, align 4
  %21 = load i32, i32* %5, align 4
  %22 = icmp sgt i32 %21, 99
  br i1 %22, label %23, label %32

23:
  %24 = load i32, i32* %6, align 4
  %25 = mul nsw i32 %24, 2
  store i32 %25, i32* %7, align 4
  %26 = call i32 @get_one(i32 0)
  %27 = icmp eq i32 %26, 1
  br i1 %27, label %28, label %31

28:
  %29 = load i32, i32* %7, align 4
  %30 = mul nsw i32 %29, 2
  store i32 %30, i32* %5, align 4
  br label %31

31:
  br label %32

32:
  br label %33

33:
  br label %11, !llvm.loop !6

34:
  %35 = load i32, i32* %5, align 4
  ret i32 %35
}
define i32 @main() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 2, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  %5 = call i32 @deepWhileBr(i32 %3, i32 %4)
  store i32 %5, i32* %2, align 4
  %6 = load i32, i32* %2, align 4
  %7 = call @putint(i32 %6)
  ret i32 0
}
