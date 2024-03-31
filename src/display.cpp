#include "../inc/display.hpp"

using namespace ftxui;

int Display() {
    int shift(0);
    Values Values;

  std::array<bool, 30> states;
 
    auto checkcontainer = Container::Vertical({});
    for (int i = 0; i < 30; ++i) {
        states[i] = false;
        checkcontainer->Add(Checkbox("Checkbox" + std::to_string(i), &states[i]));
    }

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

    auto testcomponent = Renderer([&Values] {
        auto my_image = vbox({
                canvas([&Values] (Canvas& c) {
                    auto w = c.width();
                    auto h = c.height();
                    int Highest(0);
                    int Lowest(100000);

                    std::vector<Point> Points;

                    int i(5);
                    for(auto V: Values.GetTotals()) {
                        if(V.Number > Highest) { Highest = V.Number; }
                        if(V.Number < Lowest) { Lowest = V.Number; }
                    }
                    
                    // Add a little extra to highest
                    Highest = Highest + (Highest/10);
                    i = 0;
                    for(auto V: Values.GetTotals()) {
                        Point Point = { .x = Values.ExtrapolateWidth(i, Values.GetTotals().size(), w), \
                                        .y = Values.ExtrapolateHeight(V.Number, Lowest, Highest, h), \
                                        .V = V };
                        /* c.DrawText(Point.x, Point.y + 4, std::to_string(Point.y), Color::Red); */
                        /* c.DrawText(Point.x, Point.y - 4, std::to_string(Point.y), Color::Red); */

                        Points.push_back(Point);
                        i++;
                    }
                    for(int i(0); i < Points.size()-1; i++) {
                        c.DrawPointLine(Points.at(i).x, Points.at(i).y, Points.at(i+1).x, Points.at(i+1).y);
                        c.DrawText(Points.at(i).x, Points.at(i).y-1, std::to_string(Points.at(i).V.Number), Color::Blue);
                    }
                    c.DrawText(Points.at(Points.size()-1).x, Points.at(Points.size()-1).y-1, std::to_string(Points.at(Points.size()-1).V.Number), Color::Blue);

                    /* c.DrawPointLine(0, 0, c.width(), c.height()); */
                    c.DrawText(0, 0, "width = " + std::to_string(c.width()));
                    c.DrawText(0, 4, "height = " + std::to_string(c.height()));
                    /* c.DrawBlock(c.width() - 2, c.height() - 2, Color::Blue); */
                }) | flex
        });
        return my_image | flex;
    });

    auto options = Container::Vertical({});
 
    auto container = Renderer([&] {
            auto element = vbox({
                graph(std::ref(Graph)) | flex
            }) | flex;
            return element;
    });

    int tab_index(0);
    std::vector<std::string> tab_entries = {
        "graph", "stats", "options"
    };
    auto tab_selection = Menu(&tab_entries, &tab_index, MenuOption::Horizontal());
    auto tab_content = Container::Tab({
            testcomponent,
            checkcontainer,
            options,
    }, &tab_index);

      auto main_container = Container::Vertical({
          tab_selection,
          tab_content,
      });

    auto renderer = Renderer(main_container, [&] {
        return hbox({
                separatorEmpty(),
                vbox({
                    text("MXJKM OIC") | bold | hcenter,
                    tab_selection->Render(),
                    tab_content->Render() | flex | border,
                    text("Div 4: Confirms") | bold,
                }) | flex,
                separatorEmpty()
                }) | border;
    });

    
    /* auto renderer = Renderer(container, [&] { */
    /* return container->Render() | vscroll_indicator | frame | */
    /*        size(HEIGHT, LESS_THAN, 10) | border; */
  /* }); */
 
  auto screen = ScreenInteractive::Fullscreen();

  bool refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.05s);
      // The |shift| variable belong to the main thread. `screen.Post(task)`
      // will execute the update on the thread where |screen| lives (e.g. the
      // main thread). Using `screen.Post(task)` is threadsafe.
      screen.Post([&] { shift++; });
      // After updating the state, request a new frame to be drawn. This is done
      // by simulating a new "custom" event to be handled.
      screen.Post(Event::Custom);
    }
  });

  screen.Loop(renderer);
  refresh_ui_continue = false;
  refresh_ui.join();
 
  return 0;
}

// Copyright (c) 2024, Maxamilian Kidd-May
// All rights reserved.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree. 

