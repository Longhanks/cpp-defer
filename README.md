# cpp-defer
Single header library defer statement for C++. Adapted from [LLVM](https://github.com/llvm/llvm-project) and the [Swift compiler](https://github.com/apple/swift).

## Copyright / License

The project consists of the contents of [llvm/include/llvm/ADT/ScopeExit.h](https://github.com/llvm/llvm-project/blob/master/llvm/include/llvm/ADT/ScopeExit.h) and [swift/Basic/Defer.h](https://github.com/apple/swift/blob/master/include/swift/Basic/Defer.h). Both were retrieved on the 11th of September 2019 and were available under the following licenses:

```
ScopeExit.h

Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions
See https://llvm.org/LICENSE.txt for license information
```

```
Defer.h

Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
Licensed under Apache License v2.0 with Runtime Library Exception

See https://swift.org/LICENSE.txt for license information
See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
```

Thus, this project is also available under the Apache License v2.0 with the Runtime Library Exception. For more information, see [LICENSE-llvm.txt](https://github.com/Longhanks/cpp-defer/blob/master/LICENSE-llvm.txt) and [LICENSE-swift.txt](https://github.com/Longhanks/cpp-defer/blob/master/LICENSE-swift.txt).

## Usage

See [defer.h](https://github.com/Longhanks/cpp-defer/blob/master/defer.h).

```c++
defer {
    const char s[] = "At exit\n";
    printf("%s", s);
};
```
