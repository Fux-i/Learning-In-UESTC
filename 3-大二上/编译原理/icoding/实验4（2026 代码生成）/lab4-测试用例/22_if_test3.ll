define i32 @ififElse() {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  store i32 5, i32* %1, align 4
  store i32 10, i32* %2, align 4
  %3 = load i32, i32* %1, align 4
  %4 = icmp eq i32 %3, 5
  br i1 %4, label %5, label %13

5:
  %6 = load i32, i32* %2, align 4
  %7 = icmp eq i32 %6, 10
  br i1 %7, label %8, label %9

8:
  store i32 25, i32* %1, align 4
  br label %12

9:
  %10 = load i32, i32* %1, align 4
  %11 = add nsw i32 %10, 15
  store i32 %11, i32* %1, align 4
  br label %12

12:
  br label %13

13:
  %14 = load i32, i32* %1, align 4
  ret i32 %14
}
define i32 @main() {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call i32 @ififElse()
  ret i32 %2
}
