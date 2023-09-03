#include <algorithm>
#include <chrono>
#include <iostream>
#include <vector>
#include <string_view>

bool IsWord(std::string_view const& str)
{
  return true; // TODO: implement dictionary check
}

template <
  typename Callback
>
void FindWordsWithPrefix(Callback const& callback, std::vector<char>& letters, size_t prefix_length)
{
  auto current_word = std::string_view{ letters.data(), prefix_length };
  if (IsWord(current_word))
    callback(current_word);

  if (prefix_length == letters.size())
    return;

  auto unused_letters = std::vector<char>{ std::begin(letters) + prefix_length, std::end(letters) };
  std::ranges::sort(unused_letters);
  for (auto i = 0; i < unused_letters.size(); ++i)
  {
    if (i > 0 && unused_letters[i] == unused_letters[i - 1])
      continue;
    std::ranges::copy(unused_letters, letters.data() + prefix_length);
    std::swap(letters[prefix_length], letters[prefix_length + i]);
    FindWordsWithPrefix(callback, letters, prefix_length + 1);
  }
}

template <
  typename Callback
>
void FindWords(Callback const& callback, std::vector<char>& letters)
{
  std::ranges::sort(letters);
  FindWordsWithPrefix(callback, letters, 0);
}

int main()
{
  auto printToScreen = [](std::string_view const& word) -> void { std::cout << word << std::endl; };
  auto HuntsPost_20220316_p33 = std::vector{ 'G','A', 'A', 'O', 'E', 'R', 'T', 'P', 'P' };
  auto const start_time = std::chrono::steady_clock::now();
  FindWords(printToScreen, HuntsPost_20220316_p33);
  auto const elapsed_time = std::chrono::steady_clock::now() - start_time;
  std::cout << "Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(elapsed_time).count() << "ms" << std::endl;
  return 0;
}
