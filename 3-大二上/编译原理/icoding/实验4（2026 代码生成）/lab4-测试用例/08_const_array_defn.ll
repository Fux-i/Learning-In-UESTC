@a = constant [5 x i32] [i32 0, i32 1, i32 2, i32 3, i32 4], align 16
define i32 @main() {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = load i32, i32* getelementptr inbounds ([5 x i32], [5 x i32]* @a, i64 0, i64 4), align 16
  ret i32 %2
}
