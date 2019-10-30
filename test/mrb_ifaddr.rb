##
## IFAddr Test
##

assert("IFAddr.get") do
  assert_equal("127.0.0.1/255.0.0.0", IFAddr.get("lo"))
  assert_raise(RuntimeError) do
    IFAddr.get("notfound")
  end
end
