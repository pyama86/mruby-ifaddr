##
## IFAddr Test
##

assert("IFAddr.get") do
  assert_equal("127.0.0.1", IFAddr.get("lo"))
  assert_raise(RuntimeError) do
    IFAddr.get("notfound")
  end
end
