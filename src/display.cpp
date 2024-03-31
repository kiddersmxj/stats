#include "../inc/display.hpp"

using namespace ftxui;

int Display() {
  std::array<bool, 30> states;
 
    auto checkcontainer = Container::Vertical({});
    for (int i = 0; i < 30; ++i) {
        states[i] = false;
        checkcontainer->Add(Checkbox("Checkbox" + std::to_string(i), &states[i]));
    }

  auto c = Canvas(100, 100);
 
  c.DrawText(0, 0, "This is a canvas", [](Pixel& p) {
    p.foreground_color = Color::Red;
    p.underlined = true;
  });
 
  // Triangle:
  c.DrawPointLine(10, 10, 80, 10, Color::Red);
  c.DrawPointLine(80, 10, 80, 40, Color::Blue);
  c.DrawPointLine(80, 40, 10, 10, Color::Green);

  c.DrawPointLine(50, 50, 20, 30, Color::Blue);
 
  // Circle, not filled and filled:
  /* c.DrawPointCircle(30, 50, 20); */
  /* c.DrawPointCircleFilled(40, 40, 10); */
 
  // Plot a function:
  std::vector<int> ys(100);
  for (int x = 0; x < 100; x++)
    ys[x] = int(80 + 20 * cos(x * 0.2));
  for (int x = 0; x < 99; x++) {
    c.DrawPointLine(x, ys[x], x + 1, ys[x + 1], Color::Red);
  }
 
    auto canvscont = Renderer([&] {
      auto document = canvas(&c) | border;
      return document;
      });

    auto Graph = [](int width, int height) {
        int shift = 0;
        std::vector<int> output(width);
        for (int i = 0; i < width; ++i) {
          float v = 0.5f;
          v += 0.1f * sin((i + shift) * 0.1f);
          v += 0.2f * sin((i + shift + 10) * 0.15f);
          v += 0.1f * sin((i + shift) * 0.03f);
          v *= height;
          output[i] = (int)v;
        }
    return output;
    };
 
    auto container = Renderer([&] {
            auto element = vbox({
                graph(std::ref(Graph)) | flex
            }) | flex;
            return element;
    });

    int tab_index(0);
    std::vector<std::string> tab_entries = {
        "graph", "stats",
    };
    auto tab_selection = Menu(&tab_entries, &tab_index, MenuOption::Horizontal());
    auto tab_content = Container::Tab({
            container,
            canvscont,
    }, &tab_index);

      auto main_container = Container::Vertical({
          tab_selection,
          tab_content,
      });

  auto renderer = Renderer(main_container, [&] {
    return vbox({
        text("FTXUI Demo") | bold | hcenter,
        tab_selection->Render(),
        tab_content->Render() | flex,
    }) | flex;
  });

    
    /* auto renderer = Renderer(container, [&] { */
    /* return container->Render() | vscroll_indicator | frame | */
    /*        size(HEIGHT, LESS_THAN, 10) | border; */
  /* }); */
 
  auto screen = ScreenInteractive::FitComponent();
  screen.Loop(renderer);
 
  return 0;
}

// Copyright (c) 2024, Maxamilian Kidd-May
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

