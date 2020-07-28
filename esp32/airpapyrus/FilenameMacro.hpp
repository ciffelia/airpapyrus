#ifndef FILENAME_MACRO_HPP
#define FILENAME_MACRO_HPP

// https://blog.galowicz.de/2016/02/20/short_file_macro/

namespace FilenameMacroInternal {
  using cstr = const char * const;

  static constexpr cstr past_last_slash(cstr str, cstr last_slash)
  {
    return
        *str == '\0' ? last_slash :
        *str == '/' || *str == '\\'  ? past_last_slash(str + 1, str + 1) :
        past_last_slash(str + 1, last_slash);
  }

  static constexpr cstr past_last_slash(cstr str)
  {
    return past_last_slash(str, str);
  }
}

#define __FILENAME__ ({constexpr FilenameMacroInternal::cstr sf__ {FilenameMacroInternal::past_last_slash(__FILE__)}; sf__;})

#endif
