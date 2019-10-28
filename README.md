# mruby-ifaddr   [![Build Status](https://travis-ci.org/pyama86/mruby-ifaddr.svg?branch=master)](https://travis-ci.org/pyama86/mruby-ifaddr)
IFAddr class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'pyama86/mruby-ifaddr'
end
```
## example
```ruby
p IFAddr.get("lo")
#=> "127.0.0.1"
```

## License
under the MIT License:
- see LICENSE file
