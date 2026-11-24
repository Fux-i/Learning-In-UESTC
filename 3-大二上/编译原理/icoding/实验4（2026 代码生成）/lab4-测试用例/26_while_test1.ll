define i32 @doubleWhile() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 5, i32* %1, align 4
  store i32 7, i32* %2, align 4
  br label %3

3:
  %4 = load i32, i32* %1, align 4
  %5 = icmp slt i32 %4, 100
  br i1 %5, label %6, label %18

6:
  %7 = load i32, i32* %1, align 4
  %8 = add nsw i32 %7, 30
  store i32 %8, i32* %1, align 4
  br label %9

9:
  %10 = load i32, i32* %2, align 4
  %11 = icmp slt i32 %10, 100
  br i1 %11, label %12, label %15

12:
  %13 = load i32, i32* %2, align 4
  %14 = add nsw i32 %13, 6
  store i32 %14, i32* %2, align 4
  br label %9, !llvm.loop !6

15:
  %16 = load i32, i32* %2, align 4
  %17 = sub nsw i32 %16, 100
  store i32 %17, i32* %2, align 4
  br label %3, !llvm.loop !8

18:
  %19 = load i32, i32* %2, align 4
  ret i32 %19
}
define i32 @main() {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @doubleWhile()
  ret i32 %2
}
