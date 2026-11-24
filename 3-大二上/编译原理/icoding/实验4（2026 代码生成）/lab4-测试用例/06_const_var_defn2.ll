@a = constant i32 10, align 4
@b = constant i32 5, align 4
define i32 @main() {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  ret i32 5
}
