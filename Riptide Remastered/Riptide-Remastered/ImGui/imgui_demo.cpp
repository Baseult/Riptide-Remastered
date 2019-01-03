// dear imgui, v1.53
// (demo code)

// Message to the person tempted to delete this file when integrating ImGui into their code base:
// Don't do it! Do NOT remove this file from your project! It is useful reference code that you and other users will want to refer to.
// Everything in this file will be stripped out by the linker if you don't call ImGui::ShowDemoWindow().
// During development, you can call ImGui::ShowDemoWindow() in your code to learn about various features of ImGui. Have it wired in a debug menu!
// Removing this file from your project is hindering access to documentation for everyone in your team, likely leading you to poorer usage of the library.
// Note that you can #define IMGUI_DISABLE_DEMO_WINDOWS in imconfig.h for the same effect.
// If you want to link core ImGui in your final builds but not those demo windows, #define IMGUI_DISABLE_DEMO_WINDOWS in imconfig.h and those functions will be empty.
// In other situation, when you have ImGui available you probably want this to be available for reference and execution.
// Thank you,
// -Your beloved friend, imgui_demo.cpp (that you won't delete)

// Message to beginner C/C++ programmers. About the meaning of 'static': in this demo code, we frequently we use 'static' variables inside functions. 
// We do this as a way to gather code and data in the same place, just to make the demo code faster to read, faster to write, and use less code. 
// A static variable persist across calls, so it is essentially like a global variable but declared inside the scope of the function. 
// It also happens to be a convenient way of storing simple UI related information as long as your function doesn't need to be reentrant or used in threads.
// This might be a pattern you occasionally want to use in your code, but most of the real data you would be editing is likely to be stored outside your function.

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include "imgui.h"
#include <ctype.h>          // toupper, isprint
#include <math.h>           // sqrtf, powf, cosf, sinf, floorf, ceilf
#include <stdio.h>          // vsnprintf, sscanf, printf
#include <stdlib.h>         // NULL, malloc, free, atoi
#if defined(_MSC_VER) && _MSC_VER <= 1500 // MSVC 2008 or earlier
#include <stddef.h>         // intptr_t
#else
#include <stdint.h>         // intptr_t
#endif

#ifdef _MSC_VER
#pragma warning (disable: 4996) // 'This function or variable may be unsafe': strcpy, strdup, sprintf, vsnprintf, sscanf, fopen
#define snprintf _snprintf
#endif
#ifdef __clang__
#pragma clang diagnostic ignored "-Wold-style-cast"             // warning : use of old-style cast                              // yes, they are more terse.
#pragma clang diagnostic ignored "-Wdeprecated-declarations"    // warning : 'xx' is deprecated: The POSIX name for this item.. // for strdup used in demo code (so user can copy & paste the code)
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"   // warning : cast to 'void *' from smaller integer type 'int'
#pragma clang diagnostic ignored "-Wformat-security"            // warning : warning: format string is not a string literal
#pragma clang diagnostic ignored "-Wexit-time-destructors"      // warning : declaration requires an exit-time destructor       // exit-time destruction order is undefined. if MemFree() leads to users code that has been disabled before exit it might cause problems. ImGui coding style welcomes static/globals.
#if __has_warning("-Wreserved-id-macro")
#pragma clang diagnostic ignored "-Wreserved-id-macro"          // warning : macro name is a reserved identifier                //
#endif
#elif defined(__GNUC__)
#pragma GCC diagnostic ignored "-Wint-to-pointer-cast"          // warning: cast to pointer from integer of different size
#pragma GCC diagnostic ignored "-Wformat-security"              // warning : format string is not a string literal (potentially insecure)
#pragma GCC diagnostic ignored "-Wdouble-promotion"             // warning: implicit conversion from 'float' to 'double' when passing argument to function
#pragma GCC diagnostic ignored "-Wconversion"                   // warning: conversion to 'xxxx' from 'xxxx' may alter its value
#if (__GNUC__ >= 6)
#pragma GCC diagnostic ignored "-Wmisleading-indentation"       // warning: this 'if' clause does not guard this statement      // GCC 6.0+ only. See #883 on GitHub.
#endif
#endif

// Play it nice with Windows users. Notepad in 2017 still doesn't display text data with Unix-style \n.
#ifdef _WIN32
#define IM_NEWLINE "\r\n"
#else
#define IM_NEWLINE "\n"
#endif

#define IM_MAX(_A,_B)       (((_A) >= (_B)) ? (_A) : (_B))

//-----------------------------------------------------------------------------
// DEMO CODE
//-----------------------------------------------------------------------------

#if !defined(IMGUI_DISABLE_OBSOLETE_FUNCTIONS) && defined(IMGUI_DISABLE_TEST_WINDOWS) && !defined(IMGUI_DISABLE_DEMO_WINDOWS)   // Obsolete name since 1.53, TEST->DEMO
#define IMGUI_DISABLE_DEMO_WINDOWS
#endif

#if !defined(IMGUI_DISABLE_DEMO_WINDOWS)

static void ShowExampleAppConsole(bool* p_open);
static void ShowExampleAppLog(bool* p_open);
static void ShowExampleAppLayout(bool* p_open);
static void ShowExampleAppPropertyEditor(bool* p_open);
static void ShowExampleAppLongText(bool* p_open);
static void ShowExampleAppAutoResize(bool* p_open);
static void ShowExampleAppConstrainedResize(bool* p_open);
static void ShowExampleAppFixedOverlay(bool* p_open);
static void ShowExampleAppWindowTitles(bool* p_open);
static void ShowExampleAppCustomRendering(bool* p_open);
static void ShowExampleAppMainMenuBar();
static void ShowExampleMenuFile();

static void ShowHelpMarker(const char* desc)
{
    ImGui::TextDisabled("(?)");
    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::PushTextWrapPos(450.0f);
        ImGui::TextUnformatted(desc);
        ImGui::PopTextWrapPos();
        ImGui::EndTooltip();
    }
}

void ImGui::ShowUserGuide()
{
    ImGui::BulletText("Double-click on title bar to collapse window.");
    ImGui::BulletText("Click and drag on lower right corner to resize window\n(double-click to auto fit window to its contents).");
    ImGui::BulletText("Click and drag on any empty space to move window.");
    ImGui::BulletText("TAB/SHIFT+TAB to cycle through keyboard editable fields.");
    ImGui::BulletText("CTRL+Click on a slider or drag box to input value as text.");
    if (ImGui::GetIO().FontAllowUserScaling)
        ImGui::BulletText("CTRL+Mouse Wheel to zoom window contents.");
    ImGui::BulletText("Mouse Wheel to scroll.");
    ImGui::BulletText("While editing text:\n");
    ImGui::Indent();
    ImGui::BulletText("Hold SHIFT or use mouse to select text.");
    ImGui::BulletText("CTRL+Left/Right to word jump.");
    ImGui::BulletText("CTRL+A or double-click to select all.");
    ImGui::BulletText("CTRL+X,CTRL+C,CTRL+V to use clipboard.");
    ImGui::BulletText("CTRL+Z,CTRL+Y to undo/redo.");
    ImGui::BulletText("ESCAPE to revert.");
    ImGui::BulletText("You can apply arithmetic operators +,*,/ on numerical values.\nUse +- to subtract.");
    ImGui::Unindent();
}

// Demonstrate most ImGui features (big function!)
void ImGui::ShowDemoWindow(bool* p_open)
{
    // Examples apps
    static bool show_app_main_menu_bar = false;
    static bool show_app_console = false;
    static bool show_app_log = false;
    static bool show_app_layout = false;
    static bool show_app_property_editor = false;
    static bool show_app_long_text = false;
    static bool show_app_auto_resize = false;
    static bool show_app_constrained_resize = false;
    static bool show_app_fixed_overlay = false;
    static bool show_app_window_titles = false;
    static bool show_app_custom_rendering = false;
    static bool show_app_style_editor = false;

    static bool show_app_metrics = false;
    static bool show_app_about = false;

    if (show_app_main_menu_bar)       ShowExampleAppMainMenuBar();
    if (show_app_console)             ShowExampleAppConsole(&show_app_console);
    if (show_app_log)                 ShowExampleAppLog(&show_app_log);
    if (show_app_layout)              ShowExampleAppLayout(&show_app_layout);
    if (show_app_property_editor)     ShowExampleAppPropertyEditor(&show_app_property_editor);
    if (show_app_long_text)           ShowExampleAppLongText(&show_app_long_text);
    if (show_app_auto_resize)         ShowExampleAppAutoResize(&show_app_auto_resize);
    if (show_app_constrained_resize)  ShowExampleAppConstrainedResize(&show_app_constrained_resize);
    if (show_app_fixed_overlay)       ShowExampleAppFixedOverlay(&show_app_fixed_overlay);
    if (show_app_window_titles)       ShowExampleAppWindowTitles(&show_app_window_titles);
    if (show_app_custom_rendering)    ShowExampleAppCustomRendering(&show_app_custom_rendering);

    if (show_app_metrics)             { ImGui::ShowMetricsWindow(&show_app_metrics); }
    if (show_app_style_editor)        { ImGui::Begin("Style Editor", &show_app_style_editor); ImGui::ShowStyleEditor(); ImGui::End(); }
    if (show_app_about)
    {
        ImGui::Begin("About Dear ImGui", &show_app_about, ImGuiWindowFlags_AlwaysAutoResize);
        ImGui::Text("dear imgui, %s", ImGui::GetVersion());
        ImGui::Separator();
        ImGui::Text("By Omar Cornut and all dear imgui contributors.");
        ImGui::Text("Dear ImGui is licensed under the MIT License, see LICENSE for more information.");
        ImGui::End();
    }

    static bool no_titlebar = false;
    static bool no_scrollbar = false;
    static bool no_menu = false;
    static bool no_move = false;
    static bool no_resize = false;
    static bool no_collapse = false;
    static bool no_close = false;

    // Demonstrate the various window flags. Typically you would just use the default.
    ImGuiWindowFlags window_flags = 0;
    if (no_titlebar)  window_flags |= ImGuiWindowFlags_NoTitleBar;
    if (no_scrollbar) window_flags |= ImGuiWindowFlags_NoScrollbar;
    if (!no_menu)     window_flags |= ImGuiWindowFlags_MenuBar;
    if (no_move)      window_flags |= ImGuiWindowFlags_NoMove;
    if (no_resize)    window_flags |= ImGuiWindowFlags_NoResize;
    if (no_collapse)  window_flags |= ImGuiWindowFlags_NoCollapse;
    if (no_close)     p_open = NULL; // Don't pass our bool* to Begin

    ImGui::SetNextWindowSize(ImVec2(550,680), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("ImGui Demo", p_open, window_flags))
    {
        // Early out if the window is collapsed, as an optimization.
        ImGui::End();
        return;
    }

    //ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.65f);    // 2/3 of the space for widget and 1/3 for labels
    ImGui::PushItemWidth(-140);                                 // Right align, keep 140 pixels for labels

    ImGui::Text("dear imgui says hello. (%s)", IMGUI_VERSION);

    // Menu
    if (ImGui::BeginMenuBar())
    {
        if (ImGui::BeginMenu("Menu"))
        {
            ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Examples"))
        {
            ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
            ImGui::MenuItem("Console", NULL, &show_app_console);
            ImGui::MenuItem("Log", NULL, &show_app_log);
            ImGui::MenuItem("Simple layout", NULL, &show_app_layout);
            ImGui::MenuItem("Property editor", NULL, &show_app_property_editor);
            ImGui::MenuItem("Long text display", NULL, &show_app_long_text);
            ImGui::MenuItem("Auto-resizing window", NULL, &show_app_auto_resize);
            ImGui::MenuItem("Constrained-resizing window", NULL, &show_app_constrained_resize);
            ImGui::MenuItem("Simple overlay", NULL, &show_app_fixed_overlay);
            ImGui::MenuItem("Manipulating window titles", NULL, &show_app_window_titles);
            ImGui::MenuItem("Custom rendering", NULL, &show_app_custom_rendering);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            ImGui::MenuItem("Metrics", NULL, &show_app_metrics);
            ImGui::MenuItem("Style Editor", NULL, &show_app_style_editor);
            ImGui::MenuItem("About Dear ImGui", NULL, &show_app_about);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    ImGui::Spacing();
    if (ImGui::CollapsingHeader("Help"))
    {
        ImGui::TextWrapped("This window is being created by the ShowDemoWindow() function. Please refer to the code in imgui_demo.cpp for reference.\n\n");
        ImGui::Text("USER GUIDE:");
        ImGui::ShowUserGuide();
    }

    if (ImGui::CollapsingHeader("Window options"))
    {
        ImGui::Checkbox("No titlebar", &no_titlebar); ImGui::SameLine(150);
        ImGui::Checkbox("No scrollbar", &no_scrollbar); ImGui::SameLine(300);
        ImGui::Checkbox("No menu", &no_menu);
        ImGui::Checkbox("No move", &no_move); ImGui::SameLine(150);
        ImGui::Checkbox("No resize", &no_resize); ImGui::SameLine(300);
        ImGui::Checkbox("No collapse", &no_collapse);
        ImGui::Checkbox("No close", &no_close);

        if (ImGui::TreeNode("Style"))
        {
            ImGui::ShowStyleEditor();
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Capture/Logging"))
        {
            ImGui::TextWrapped("The logging API redirects all text output so you can easily capture the content of a window or a block. Tree nodes can be automatically expanded. You can also call ImGui::LogText() to output directly to the log without a visual output.");
            ImGui::LogButtons();
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Widgets"))
    {
        if (ImGui::TreeNode("Basic"))
        {
            static int clicked = 0;
            if (ImGui::Button("Button")) 
                clicked++;
            if (clicked & 1)
            {
                ImGui::SameLine();
                ImGui::Text("Thanks for clicking me!");
            }

            static bool check = true;
            ImGui::Checkbox("checkbox", &check);

            static int e = 0;
            ImGui::RadioButton("radio a", &e, 0); ImGui::SameLine();
            ImGui::RadioButton("radio b", &e, 1); ImGui::SameLine();
            ImGui::RadioButton("radio c", &e, 2);

            // Color buttons, demonstrate using PushID() to add unique identifier in the ID stack, and changing style.
            for (int i = 0; i < 7; i++)
            {
                if (i > 0) ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i/7.0f, 0.6f, 0.6f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i/7.0f, 0.7f, 0.7f));
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i/7.0f, 0.8f, 0.8f));
                ImGui::Button("Click");
                ImGui::PopStyleColor(3);
                ImGui::PopID();
            }

            ImGui::Text("Hover over me");
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("I am a tooltip");

            ImGui::SameLine();
            ImGui::Text("- or me");
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                ImGui::Text("I am a fancy tooltip");
                static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
                ImGui::PlotLines("Curve", arr, IM_ARRAYSIZE(arr));
                ImGui::EndTooltip();
            }

            // Testing ImGuiOnceUponAFrame helper.
            //static ImGuiOnceUponAFrame once;
            //for (int i = 0; i < 5; i++)
            //    if (once)
            //        ImGui::Text("This will be displayed only once.");

            ImGui::Separator();

            ImGui::LabelText("label", "Value");

            {
                // Simplified one-liner Combo() API, using values packed in a single constant string
                static int current_item_1 = 1;
                ImGui::Combo("combo", &current_item_1, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
                //ImGui::Combo("combo w/ array of char*", &current_item_2_idx, items, IM_ARRAYSIZE(items));   // Combo using proper array. You can also pass a callback to retrieve array value, no need to create/copy an array just for that.

                // General BeginCombo() API, you have full control over your selection data and display type
                const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO", "PPPP", "QQQQQQQQQQ", "RRR", "SSSS" };
                static const char* current_item_2 = NULL;
                if (ImGui::BeginCombo("combo 2", current_item_2)) // The second parameter is the label previewed before opening the combo.
                {
                    for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                    {
                        bool is_selected = (current_item_2 == items[n]); // You can store your selection however you want, outside or inside your objects
                        if (ImGui::Selectable(items[n], is_selected))
                            current_item_2 = items[n];
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();   // Set the initial focus when opening the combo (scrolling + for keyboard navigation support in the upcoming navigation branch)
                    }
                    ImGui::EndCombo();
                }
            }

            {
                static char str0[128] = "Hello, world!";
                static int i0=123;
                static float f0=0.001f;
                ImGui::InputText("input text", str0, IM_ARRAYSIZE(str0));
                ImGui::SameLine(); ShowHelpMarker("Hold SHIFT or use mouse to select text.\n" "CTRL+Left/Right to word jump.\n" "CTRL+A or double-click to select all.\n" "CTRL+X,CTRL+C,CTRL+V clipboard.\n" "CTRL+Z,CTRL+Y undo/redo.\n" "ESCAPE to revert.\n");

                ImGui::InputInt("input int", &i0);
                ImGui::SameLine(); ShowHelpMarker("You can apply arithmetic operators +,*,/ on numerical values.\n  e.g. [ 100 ], input \'*2\', result becomes [ 200 ]\nUse +- to subtract.\n");

                ImGui::InputFloat("input float", &f0, 0.01f, 1.0f);

                static float vec4a[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
                ImGui::InputFloat3("input float3", vec4a);
            }

            {
                static int i1=50, i2=42;
                ImGui::DragInt("drag int", &i1, 1);
                ImGui::SameLine(); ShowHelpMarker("Click and drag to edit value.\nHold SHIFT/ALT for faster/slower edit.\nDouble-click or CTRL+click to input value.");

                ImGui::DragInt("drag int 0..100", &i2, 1, 0, 100, "%.0f%%");

                static float f1=1.00f, f2=0.0067f;
                ImGui::DragFloat("drag float", &f1, 0.005f);
                ImGui::DragFloat("drag small float", &f2, 0.0001f, 0.0f, 0.0f, "%.06f ns");
            }

            {
                static int i1=0;
                ImGui::SliderInt("slider int", &i1, -1, 3);
                ImGui::SameLine(); ShowHelpMarker("CTRL+click to input value.");

                static float f1=0.123f, f2=0.0f;
                ImGui::SliderFloat("slider float", &f1, 0.0f, 1.0f, "ratio = %.3f");
                ImGui::SliderFloat("slider log float", &f2, -10.0f, 10.0f, "%.4f", 3.0f);
                static float angle = 0.0f;
                ImGui::SliderAngle("slider angle", &angle);
            }

            static float col1[3] = { 1.0f,0.0f,0.2f };
            static float col2[4] = { 0.4f,0.7f,0.0f,0.5f };
            ImGui::ColorEdit3("color 1", col1);
            ImGui::SameLine(); ShowHelpMarker("Click on the colored square to open a color picker.\nRight-click on the colored square to show options.\nCTRL+click on individual component to input value.\n");

            ImGui::ColorEdit4("color 2", col2);

            const char* listbox_items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" };
            static int listbox_item_current = 1;
            ImGui::ListBox("listbox\n(single select)", &listbox_item_current, listbox_items, IM_ARRAYSIZE(listbox_items), 4);

            //static int listbox_item_current2 = 2;
            //ImGui::PushItemWidth(-1);
            //ImGui::ListBox("##listbox2", &listbox_item_current2, listbox_items, IM_ARRAYSIZE(listbox_items), 4);
            //ImGui::PopItemWidth();

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Trees"))
        {
            if (ImGui::TreeNode("Basic trees"))
            {
                for (int i = 0; i < 5; i++)
                    if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
                    {
                        ImGui::Text("blah blah");
                        ImGui::SameLine(); 
                        if (ImGui::SmallButton("print")) printf("Child %d pressed", i);
                        ImGui::TreePop();
                    }
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Advanced, with Selectable nodes"))
            {
                ShowHelpMarker("This is a more standard looking tree with selectable nodes.\nClick to select, CTRL+Click to toggle, click on arrows or double-click to open.");
                static bool align_label_with_current_x_position = false;
                ImGui::Checkbox("Align label with current X position)", &align_label_with_current_x_position);
                ImGui::Text("Hello!");
                if (align_label_with_current_x_position)
                    ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

                static int selection_mask = (1 << 2); // Dumb representation of what may be user-side selection state. You may carry selection state inside or outside your objects in whatever format you see fit.
                int node_clicked = -1;                // Temporary storage of what node we have clicked to process selection at the end of the loop. May be a pointer to your own node type, etc.
                ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize()*3); // Increase spacing to differentiate leaves from expanded contents.
                for (int i = 0; i < 6; i++)
                {
                    // Disable the default open on single-click behavior and pass in Selected flag according to our selection state.
                    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((selection_mask & (1 << i)) ? ImGuiTreeNodeFlags_Selected : 0);
                    if (i < 3)
                    {
                        // Node
                        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
                        if (ImGui::IsItemClicked()) 
                            node_clicked = i;
                        if (node_open)
                        {
                            ImGui::Text("Blah blah\nBlah Blah");
                            ImGui::TreePop();
                        }
                    }
                    else
                    {
                        // Leaf: The only reason we have a TreeNode at all is to allow selection of the leaf. Otherwise we can use BulletText() or TreeAdvanceToLabelPos()+Text().
                        node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                        ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                        if (ImGui::IsItemClicked()) 
                            node_clicked = i;
                    }
                }
                if (node_clicked != -1)
                {
                    // Update selection state. Process outside of tree loop to avoid visual inconsistencies during the clicking-frame.
                    if (ImGui::GetIO().KeyCtrl)
                        selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                    else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, this commented bit preserve selection when clicking on item that is part of the selection
                        selection_mask = (1 << node_clicked);           // Click to single-select
                }
                ImGui::PopStyleVar();
                if (align_label_with_current_x_position)
                    ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Collapsing Headers"))
        {
            static bool closable_group = true;
            ImGui::Checkbox("Enable extra group", &closable_group);
            if (ImGui::CollapsingHeader("Header"))
            {
                ImGui::Text("IsItemHovered: %d", IsItemHovered());
                for (int i = 0; i < 5; i++)
                    ImGui::Text("Some content %d", i);
            }
            if (ImGui::CollapsingHeader("Header with a close button", &closable_group))
            {
                ImGui::Text("IsItemHovered: %d", IsItemHovered());
                for (int i = 0; i < 5; i++)
                    ImGui::Text("More content %d", i);
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Bullets"))
        {
            ImGui::BulletText("Bullet point 1");
            ImGui::BulletText("Bullet point 2\nOn multiple lines");
            ImGui::Bullet(); ImGui::Text("Bullet point 3 (two calls)");
            ImGui::Bullet(); ImGui::SmallButton("Button");
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Text"))
        {
            if (ImGui::TreeNode("Colored Text"))
            {
                // Using shortcut. You can use PushStyleColor()/PopStyleColor() for more flexibility.
                ImGui::TextColored(ImVec4(1.0f,0.0f,1.0f,1.0f), "Pink");
                ImGui::TextColored(ImVec4(1.0f,1.0f,0.0f,1.0f), "Yellow");
                ImGui::TextDisabled("Disabled");
                ImGui::SameLine(); ShowHelpMarker("The TextDisabled color is stored in ImGuiStyle.");
                ImGui::TreePop();
            }

            if (ImGui::TreeNode("Word Wrapping"))
            {
                // Using shortcut. You can use PushTextWrapPos()/PopTextWrapPos() for more flexibility.
                ImGui::TextWrapped("This text should automatically wrap on the edge of the window. The current implementation for text wrapping follows simple rules suitable for English and possibly other languages.");
                ImGui::Spacing();

                static float wrap_width = 200.0f;
                ImGui::SliderFloat("Wrap width", &wrap_width, -20, 600, "%.0f");

                ImGui::Text("Test paragraph 1:");
                ImVec2 pos = ImGui::GetCursorScreenPos();
                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + wrap_width, pos.y), ImVec2(pos.x + wrap_width + 10, pos.y + ImGui::GetTextLineHeight()), IM_COL32(255,0,255,255));
                ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
                ImGui::Text("The lazy dog is a good dog. This paragraph is made to fit within %.0f pixels. Testing a 1 character word. The quick brown fox jumps over the lazy dog.", wrap_width);
                ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255,255,0,255));
                ImGui::PopTextWrapPos();

                ImGui::Text("Test paragraph 2:");
                pos = ImGui::GetCursorScreenPos();
                ImGui::GetWindowDrawList()->AddRectFilled(ImVec2(pos.x + wrap_width, pos.y), ImVec2(pos.x + wrap_width + 10, pos.y + ImGui::GetTextLineHeight()), IM_COL32(255,0,255,255));
                ImGui::PushTextWrapPos(ImGui::GetCursorPos().x + wrap_width);
                ImGui::Text("aaaaaaaa bbbbbbbb, c cccccccc,dddddddd. d eeeeeeee   ffffffff. gggggggg!hhhhhhhh");
                ImGui::GetWindowDrawList()->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255,255,0,255));
                ImGui::PopTextWrapPos();

                ImGui::TreePop();
            }

            if (ImGui::TreeNode("UTF-8 Text"))
            {
                // UTF-8 test with Japanese characters
                // (needs a suitable font, try Arial Unicode or M+ fonts http://mplus-fonts.sourceforge.jp/mplus-outline-fonts/index-en.html)
                // - From C++11 you can use the u8"my text" syntax to encode literal strings as UTF-8
                // - For earlier compiler, you may be able to encode your sources as UTF-8 (e.g. Visual Studio save your file as 'UTF-8 without signature')
                // - HOWEVER, FOR THIS DEMO FILE, BECAUSE WE WANT TO SUPPORT COMPILER, WE ARE *NOT* INCLUDING RAW UTF-8 CHARACTERS IN THIS SOURCE FILE.
                //   Instead we are encoding a few string with hexadecimal constants. Don't do this in your application!
                // Note that characters values are preserved even by InputText() if the font cannot be displayed, so you can safely copy & paste garbled characters into another application.
                ImGui::TextWrapped("CJK text will only appears if the font was loaded with the appropriate CJK character ranges. Call io.Font->LoadFromFileTTF() manually to load extra character ranges.");
                ImGui::Text("Hiragana: \xe3\x81\x8b\xe3\x81\x8d\xe3\x81\x8f\xe3\x81\x91\xe3\x81\x93 (kakikukeko)");
                ImGui::Text("Kanjis: \xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e (nihongo)");
                static char buf[32] = "\xe6\x97\xa5\xe6\x9c\xac\xe8\xaa\x9e"; // "nihongo"
                ImGui::InputText("UTF-8 input", buf, IM_ARRAYSIZE(buf));
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Images"))
        {
            ImGui::TextWrapped("Below we are displaying the font texture (which is the only texture we have access to in this demo). Use the 'ImTextureID' type as storage to pass pointers or identifier to your own texture data. Hover the texture for a zoomed view!");
            ImGuiIO& io = ImGui::GetIO();

            // Here we are grabbing the font texture because that's the only one we have access to inside the demo code.
            // Remember that ImTextureID is just storage for whatever you want it to be, it is essentially a value that will be passed to the render function inside the ImDrawCmd structure.
            // If you use one of the default imgui_impl_XXXX.cpp renderer, they all have comments at the top of their file to specify what they expect to be stored in ImTextureID.
            // (for example, the imgui_impl_dx11.cpp renderer expect a 'ID3D11ShaderResourceView*' pointer. The imgui_impl_glfw_gl3.cpp renderer expect a GLuint OpenGL texture identifier etc.)
            // If you decided that ImTextureID = MyEngineTexture*, then you can pass your MyEngineTexture* pointers to ImGui::Image(), and gather width/height through your own functions, etc.
            // Using ShowMetricsWindow() as a "debugger" to inspect the draw data that are being passed to your render will help you debug issues if you are confused about this.
            // Consider using the lower-level ImDrawList::AddImage() API, via ImGui::GetWindowDrawList()->AddImage().
            ImTextureID my_tex_id = io.Fonts->TexID; 
            float my_tex_w = (float)io.Fonts->TexWidth;
            float my_tex_h = (float)io.Fonts->TexHeight;

            ImGui::Text("%.0fx%.0f", my_tex_w, my_tex_h);
            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImGui::Image(my_tex_id, ImVec2(my_tex_w, my_tex_h), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
            if (ImGui::IsItemHovered())
            {
                ImGui::BeginTooltip();
                float focus_sz = 32.0f;
                float focus_x = io.MousePos.x - pos.x - focus_sz * 0.5f; if (focus_x < 0.0f) focus_x = 0.0f; else if (focus_x > my_tex_w - focus_sz) focus_x = my_tex_w - focus_sz;
                float focus_y = io.MousePos.y - pos.y - focus_sz * 0.5f; if (focus_y < 0.0f) focus_y = 0.0f; else if (focus_y > my_tex_h - focus_sz) focus_y = my_tex_h - focus_sz;
                ImGui::Text("Min: (%.2f, %.2f)", focus_x, focus_y);
                ImGui::Text("Max: (%.2f, %.2f)", focus_x + focus_sz, focus_y + focus_sz);
                ImVec2 uv0 = ImVec2((focus_x) / my_tex_w, (focus_y) / my_tex_h);
                ImVec2 uv1 = ImVec2((focus_x + focus_sz) / my_tex_w, (focus_y + focus_sz) / my_tex_h);
                ImGui::Image(my_tex_id, ImVec2(128,128), uv0, uv1, ImColor(255,255,255,255), ImColor(255,255,255,128));
                ImGui::EndTooltip();
            }
            ImGui::TextWrapped("And now some textured buttons..");
            static int pressed_count = 0;
            for (int i = 0; i < 8; i++)
            {
                ImGui::PushID(i);
                int frame_padding = -1 + i;     // -1 = uses default padding
                if (ImGui::ImageButton(my_tex_id, ImVec2(32,32), ImVec2(0,0), ImVec2(32.0f/my_tex_w,32/my_tex_h), frame_padding, ImColor(0,0,0,255)))
                    pressed_count += 1;
                ImGui::PopID();
                ImGui::SameLine();
            }
            ImGui::NewLine();
            ImGui::Text("Pressed %d times.", pressed_count);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Selectables"))
        {
            if (ImGui::TreeNode("Basic"))
            {
                static bool selected[4] = { false, true, false, false };
                ImGui::Selectable("1. I am selectable", &selected[0]);
                ImGui::Selectable("2. I am selectable", &selected[1]);
                ImGui::Text("3. I am not selectable");
                ImGui::Selectable("4. I am selectable", &selected[2]);
                if (ImGui::Selectable("5. I am double clickable", selected[3], ImGuiSelectableFlags_AllowDoubleClick))
                    if (ImGui::IsMouseDoubleClicked(0))
                        selected[3] = !selected[3];
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Rendering more text into the same block"))
            {
                static bool selected[3] = { false, false, false };
                ImGui::Selectable("main.c", &selected[0]);    ImGui::SameLine(300); ImGui::Text(" 2,345 bytes");
                ImGui::Selectable("Hello.cpp", &selected[1]); ImGui::SameLine(300); ImGui::Text("12,345 bytes");
                ImGui::Selectable("Hello.h", &selected[2]);   ImGui::SameLine(300); ImGui::Text(" 2,345 bytes");
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("In columns"))
            {
                ImGui::Columns(3, NULL, false);
                static bool selected[16] = { 0 };
                for (int i = 0; i < 16; i++)
                {
                    char label[32]; sprintf(label, "Item %d", i);
                    if (ImGui::Selectable(label, &selected[i])) {}
                    ImGui::NextColumn();
                }
                ImGui::Columns(1);
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("Grid"))
            {
                static bool selected[16] = { true, false, false, false, false, true, false, false, false, false, true, false, false, false, false, true };
                for (int i = 0; i < 16; i++)
                {
                    ImGui::PushID(i);
                    if (ImGui::Selectable("Sailor", &selected[i], 0, ImVec2(50,50)))
                    {
                        int x = i % 4, y = i / 4;
                        if (x > 0) selected[i - 1] ^= 1;
                        if (x < 3) selected[i + 1] ^= 1;
                        if (y > 0) selected[i - 4] ^= 1;
                        if (y < 3) selected[i + 4] ^= 1;
                    }
                    if ((i % 4) < 3) ImGui::SameLine();
                    ImGui::PopID();
                }
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Filtered Text Input"))
        {
            static char buf1[64] = ""; ImGui::InputText("default", buf1, 64);
            static char buf2[64] = ""; ImGui::InputText("decimal", buf2, 64, ImGuiInputTextFlags_CharsDecimal);
            static char buf3[64] = ""; ImGui::InputText("hexadecimal", buf3, 64, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_CharsUppercase);
            static char buf4[64] = ""; ImGui::InputText("uppercase", buf4, 64, ImGuiInputTextFlags_CharsUppercase);
            static char buf5[64] = ""; ImGui::InputText("no blank", buf5, 64, ImGuiInputTextFlags_CharsNoBlank);
            struct TextFilters { static int FilterImGuiLetters(ImGuiTextEditCallbackData* data) { if (data->EventChar < 256 && strchr("imgui", (char)data->EventChar)) return 0; return 1; } };
            static char buf6[64] = ""; ImGui::InputText("\"imgui\" letters", buf6, 64, ImGuiInputTextFlags_CallbackCharFilter, TextFilters::FilterImGuiLetters);

            ImGui::Text("Password input");
            static char bufpass[64] = "password123";
            ImGui::InputText("password", bufpass, 64, ImGuiInputTextFlags_Password | ImGuiInputTextFlags_CharsNoBlank);
            ImGui::SameLine(); ShowHelpMarker("Display all characters as '*'.\nDisable clipboard cut and copy.\nDisable logging.\n");
            ImGui::InputText("password (clear)", bufpass, 64, ImGuiInputTextFlags_CharsNoBlank);

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Multi-line Text Input"))
        {
            static bool read_only = false;
            static char text[1024*16] =
                "/*\n"
                " The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
                " the hexadecimal encoding of one offending instruction,\n"
                " more formally, the invalid operand with locked CMPXCHG8B\n"
                " instruction bug, is a design flaw in the majority of\n"
                " Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
                " processors (all in the P5 microarchitecture).\n"
                "*/\n\n"
                "label:\n"
                "\tlock cmpxchg8b eax\n";

            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
            ImGui::Checkbox("Read-only", &read_only);
            ImGui::PopStyleVar();
            ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-1.0f, ImGui::GetTextLineHeight() * 16), ImGuiInputTextFlags_AllowTabInput | (read_only ? ImGuiInputTextFlags_ReadOnly : 0));
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Plots widgets"))
        {
            static bool animate = true;
            ImGui::Checkbox("Animate", &animate);

            static float arr[] = { 0.6f, 0.1f, 1.0f, 0.5f, 0.92f, 0.1f, 0.2f };
            ImGui::PlotLines("Frame Times", arr, IM_ARRAYSIZE(arr));

            // Create a dummy array of contiguous float values to plot
            // Tip: If your float aren't contiguous but part of a structure, you can pass a pointer to your first float and the sizeof() of your structure in the Stride parameter.
            static float values[90] = { 0 };
            static int values_offset = 0;
            static float refresh_time = 0.0f;
            if (!animate || refresh_time == 0.0f)
                refresh_time = ImGui::GetTime();
            while (refresh_time < ImGui::GetTime()) // Create dummy data at fixed 60 hz rate for the demo
            {
                static float phase = 0.0f;
                values[values_offset] = cosf(phase);
                values_offset = (values_offset+1) % IM_ARRAYSIZE(values);
                phase += 0.10f*values_offset;
                refresh_time += 1.0f/60.0f;
            }
            ImGui::PlotLines("Lines", values, IM_ARRAYSIZE(values), values_offset, "avg 0.0", -1.0f, 1.0f, ImVec2(0,80));
            ImGui::PlotHistogram("Histogram", arr, IM_ARRAYSIZE(arr), 0, NULL, 0.0f, 1.0f, ImVec2(0,80));

            // Use functions to generate output
            // FIXME: This is rather awkward because current plot API only pass in indices. We probably want an API passing floats and user provide sample rate/count.
            struct Funcs
            {
                static float Sin(void*, int i) { return sinf(i * 0.1f); }
                static float Saw(void*, int i) { return (i & 1) ? 1.0f : -1.0f; }
            };
            static int func_type = 0, display_count = 70;
            ImGui::Separator();
            ImGui::PushItemWidth(100); ImGui::Combo("func", &func_type, "Sin\0Saw\0"); ImGui::PopItemWidth();
            ImGui::SameLine();
            ImGui::SliderInt("Sample count", &display_count, 1, 400);
            float (*func)(void*, int) = (func_type == 0) ? Funcs::Sin : Funcs::Saw;
            ImGui::PlotLines("Lines", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0,80));
            ImGui::PlotHistogram("Histogram", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, ImVec2(0,80));
            ImGui::Separator();

            // Animate a simple progress bar
            static float progress = 0.0f, progress_dir = 1.0f;
            if (animate)
            {
                progress += progress_dir * 0.4f * ImGui::GetIO().DeltaTime;
                if (progress >= +1.1f) { progress = +1.1f; progress_dir *= -1.0f; }
                if (progress <= -0.1f) { progress = -0.1f; progress_dir *= -1.0f; }
            }

            // Typically we would use ImVec2(-1.0f,0.0f) to use all available width, or ImVec2(width,0.0f) for a specified width. ImVec2(0.0f,0.0f) uses ItemWidth.
            ImGui::ProgressBar(progress, ImVec2(0.0f,0.0f));
            ImGui::SameLine(0.0f, ImGui::GetStyle().ItemInnerSpacing.x);
            ImGui::Text("Progress Bar");

            float progress_saturated = (progress < 0.0f) ? 0.0f : (progress > 1.0f) ? 1.0f : progress;
            char buf[32];
            sprintf(buf, "%d/%d", (int)(progress_saturated*1753), 1753);
            ImGui::ProgressBar(progress, ImVec2(0.f,0.f), buf);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Color/Picker Widgets"))
        {
            static ImVec4 color = ImColor(114, 144, 154, 200);

            static bool hdr = false;
            static bool alpha_preview = true;
            static bool alpha_half_preview = false;
            static bool options_menu = true;
            ImGui::Checkbox("With HDR", &hdr); ImGui::SameLine(); ShowHelpMarker("Currently all this does is to lift the 0..1 limits on dragging widgets.");
            ImGui::Checkbox("With Alpha Preview", &alpha_preview);
            ImGui::Checkbox("With Half Alpha Preview", &alpha_half_preview);
            ImGui::Checkbox("With Options Menu", &options_menu); ImGui::SameLine(); ShowHelpMarker("Right-click on the individual color widget to show options.");
            int misc_flags = (hdr ? ImGuiColorEditFlags_HDR : 0) | (alpha_half_preview ? ImGuiColorEditFlags_AlphaPreviewHalf : (alpha_preview ? ImGuiColorEditFlags_AlphaPreview : 0)) | (options_menu ? 0 : ImGuiColorEditFlags_NoOptions);

            ImGui::Text("Color widget:");
            ImGui::SameLine(); ShowHelpMarker("Click on the colored square to open a color picker.\nCTRL+click on individual component to input value.\n");
            ImGui::ColorEdit3("MyColor##1", (float*)&color, misc_flags);

            ImGui::Text("Color widget HSV with Alpha:");
            ImGui::ColorEdit4("MyColor##2", (float*)&color, ImGuiColorEditFlags_HSV | misc_flags);

            ImGui::Text("Color widget with Float Display:");
            ImGui::ColorEdit4("MyColor##2f", (float*)&color, ImGuiColorEditFlags_Float | misc_flags);

            ImGui::Text("Color button with Picker:");
            ImGui::SameLine(); ShowHelpMarker("With the ImGuiColorEditFlags_NoInputs flag you can hide all the slider/text inputs.\nWith the ImGuiColorEditFlags_NoLabel flag you can pass a non-empty label which will only be used for the tooltip and picker popup.");
            ImGui::ColorEdit4("MyColor##3", (float*)&color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | misc_flags);

            ImGui::Text("Color button with Custom Picker Popup:");

            // Generate a dummy palette
            static bool saved_palette_inited = false;
            static ImVec4 saved_palette[32];
            if (!saved_palette_inited)
                for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
                {
                    ImGui::ColorConvertHSVtoRGB(n / 31.0f, 0.8f, 0.8f, saved_palette[n].x, saved_palette[n].y, saved_palette[n].z);
                    saved_palette[n].w = 1.0f; // Alpha
                }
            saved_palette_inited = true;

            static ImVec4 backup_color;
            bool open_popup = ImGui::ColorButton("MyColor##3b", color, misc_flags);
            ImGui::SameLine();
            open_popup |= ImGui::Button("Palette");
            if (open_popup)
            {
                ImGui::OpenPopup("mypicker");
                backup_color = color;
            }
            if (ImGui::BeginPopup("mypicker"))
            {
                // FIXME: Adding a drag and drop example here would be perfect!
                ImGui::Text("MY CUSTOM COLOR PICKER WITH AN AMAZING PALETTE!");
                ImGui::Separator();
                ImGui::ColorPicker4("##picker", (float*)&color, misc_flags | ImGuiColorEditFlags_NoSidePreview | ImGuiColorEditFlags_NoSmallPreview);
                ImGui::SameLine();
                ImGui::BeginGroup();
                ImGui::Text("Current");
                ImGui::ColorButton("##current", color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60,40));
                ImGui::Text("Previous");
                if (ImGui::ColorButton("##previous", backup_color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_AlphaPreviewHalf, ImVec2(60,40)))
                    color = backup_color;
                ImGui::Separator();
                ImGui::Text("Palette");
                for (int n = 0; n < IM_ARRAYSIZE(saved_palette); n++)
                {
                    ImGui::PushID(n);
                    if ((n % 8) != 0)
                        ImGui::SameLine(0.0f, ImGui::GetStyle().ItemSpacing.y);
                    if (ImGui::ColorButton("##palette", saved_palette[n], ImGuiColorEditFlags_NoAlpha | ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoTooltip, ImVec2(20,20)))
                        color = ImVec4(saved_palette[n].x, saved_palette[n].y, saved_palette[n].z, color.w); // Preserve alpha!

                    if (ImGui::BeginDragDropTarget())
                    {
                        if (const ImGuiPayload* payload = AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_3F))
                            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 3);
                        if (const ImGuiPayload* payload = AcceptDragDropPayload(IMGUI_PAYLOAD_TYPE_COLOR_4F))
                            memcpy((float*)&saved_palette[n], payload->Data, sizeof(float) * 4);
                        EndDragDropTarget();
                    }

                    ImGui::PopID();
                }
                ImGui::EndGroup();
                ImGui::EndPopup();
            }

            ImGui::Text("Color button only:");
            ImGui::ColorButton("MyColor##3c", *(ImVec4*)&color, misc_flags, ImVec2(80,80));

            ImGui::Text("Color picker:");
            static bool alpha = true;
            static bool alpha_bar = true;
            static bool side_preview = true;
            static bool ref_color = false;
            static ImVec4 ref_color_v(1.0f,0.0f,1.0f,0.5f);
            static int inputs_mode = 2;
            static int picker_mode = 0;
            ImGui::Checkbox("With Alpha", &alpha);
            ImGui::Checkbox("With Alpha Bar", &alpha_bar);
            ImGui::Checkbox("With Side Preview", &side_preview);
            if (side_preview)
            {
                ImGui::SameLine();
                ImGui::Checkbox("With Ref Color", &ref_color);
                if (ref_color)
                {
                    ImGui::SameLine();
                    ImGui::ColorEdit4("##RefColor", &ref_color_v.x, ImGuiColorEditFlags_NoInputs | misc_flags);
                }
            }
            ImGui::Combo("Inputs Mode", &inputs_mode, "All Inputs\0No Inputs\0RGB Input\0HSV Input\0HEX Input\0");
            ImGui::Combo("Picker Mode", &picker_mode, "Auto/Current\0Hue bar + SV rect\0Hue wheel + SV triangle\0");
            ImGui::SameLine(); ShowHelpMarker("User can right-click the picker to change mode.");
            ImGuiColorEditFlags flags = misc_flags;
            if (!alpha) flags |= ImGuiColorEditFlags_NoAlpha; // This is by default if you call ColorPicker3() instead of ColorPicker4()
            if (alpha_bar) flags |= ImGuiColorEditFlags_AlphaBar;
            if (!side_preview) flags |= ImGuiColorEditFlags_NoSidePreview;
            if (picker_mode == 1) flags |= ImGuiColorEditFlags_PickerHueBar;
            if (picker_mode == 2) flags |= ImGuiColorEditFlags_PickerHueWheel;
            if (inputs_mode == 1) flags |= ImGuiColorEditFlags_NoInputs;
            if (inputs_mode == 2) flags |= ImGuiColorEditFlags_RGB;
            if (inputs_mode == 3) flags |= ImGuiColorEditFlags_HSV;
            if (inputs_mode == 4) flags |= ImGuiColorEditFlags_HEX;
            ImGui::ColorPicker4("MyColor##4", (float*)&color, flags, ref_color ? &ref_color_v.x : NULL);

            ImGui::Text("Programmatically set defaults/options:");
            ImGui::SameLine(); ShowHelpMarker("SetColorEditOptions() is designed to allow you to set boot-time default.\nWe don't have Push/Pop functions because you can force options on a per-widget basis if needed, and the user can change non-forced ones with the options menu.\nWe don't have a getter to avoid encouraging you to persistently save values that aren't forward-compatible.");
            if (ImGui::Button("Uint8 + HSV"))
                ImGui::SetColorEditOptions(ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_HSV);
            ImGui::SameLine();
            if (ImGui::Button("Float + HDR"))
                ImGui::SetColorEditOptions(ImGuiColorEditFlags_Float | ImGuiColorEditFlags_RGB);

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Range Widgets"))
        {
            static float begin = 10, end = 90;
            static int begin_i = 100, end_i = 1000;
            ImGui::DragFloatRange2("range", &begin, &end, 0.25f, 0.0f, 100.0f, "Min: %.1f %%", "Max: %.1f %%");
            ImGui::DragIntRange2("range int (no bounds)", &begin_i, &end_i, 5, 0, 0, "Min: %.0f units", "Max: %.0f units");
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Multi-component Widgets"))
        {
            static float vec4f[4] = { 0.10f, 0.20f, 0.30f, 0.44f };
            static int vec4i[4] = { 1, 5, 100, 255 };

            ImGui::InputFloat2("input float2", vec4f);
            ImGui::DragFloat2("drag float2", vec4f, 0.01f, 0.0f, 1.0f);
            ImGui::SliderFloat2("slider float2", vec4f, 0.0f, 1.0f);
            ImGui::DragInt2("drag int2", vec4i, 1, 0, 255);
            ImGui::InputInt2("input int2", vec4i);
            ImGui::SliderInt2("slider int2", vec4i, 0, 255);
            ImGui::Spacing();

            ImGui::InputFloat3("input float3", vec4f);
            ImGui::DragFloat3("drag float3", vec4f, 0.01f, 0.0f, 1.0f);
            ImGui::SliderFloat3("slider float3", vec4f, 0.0f, 1.0f);
            ImGui::DragInt3("drag int3", vec4i, 1, 0, 255);
            ImGui::InputInt3("input int3", vec4i);
            ImGui::SliderInt3("slider int3", vec4i, 0, 255);
            ImGui::Spacing();

            ImGui::InputFloat4("input float4", vec4f);
            ImGui::DragFloat4("drag float4", vec4f, 0.01f, 0.0f, 1.0f);
            ImGui::SliderFloat4("slider float4", vec4f, 0.0f, 1.0f);
            ImGui::InputInt4("input int4", vec4i);
            ImGui::DragInt4("drag int4", vec4i, 1, 0, 255);
            ImGui::SliderInt4("slider int4", vec4i, 0, 255);

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Vertical Sliders"))
        {
            const float spacing = 4;
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(spacing, spacing));

            static int int_value = 0;
            ImGui::VSliderInt("##int", ImVec2(18,160), &int_value, 0, 5);
            ImGui::SameLine();

            static float values[7] = { 0.0f, 0.60f, 0.35f, 0.9f, 0.70f, 0.20f, 0.0f };
            ImGui::PushID("set1");
            for (int i = 0; i < 7; i++)
            {
                if (i > 0) ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleColor(ImGuiCol_FrameBg, (ImVec4)ImColor::HSV(i/7.0f, 0.5f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, (ImVec4)ImColor::HSV(i/7.0f, 0.6f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_FrameBgActive, (ImVec4)ImColor::HSV(i/7.0f, 0.7f, 0.5f));
                ImGui::PushStyleColor(ImGuiCol_SliderGrab, (ImVec4)ImColor::HSV(i/7.0f, 0.9f, 0.9f));
                ImGui::VSliderFloat("##v", ImVec2(18,160), &values[i], 0.0f, 1.0f, "");
                if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                    ImGui::SetTooltip("%.3f", values[i]);
                ImGui::PopStyleColor(4);
                ImGui::PopID();
            }
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::PushID("set2");
            static float values2[4] = { 0.20f, 0.80f, 0.40f, 0.25f };
            const int rows = 3;
            const ImVec2 small_slider_size(18, (160.0f-(rows-1)*spacing)/rows);
            for (int nx = 0; nx < 4; nx++)
            {
                if (nx > 0) ImGui::SameLine();
                ImGui::BeginGroup();
                for (int ny = 0; ny < rows; ny++)
                {
                    ImGui::PushID(nx*rows+ny);
                    ImGui::VSliderFloat("##v", small_slider_size, &values2[nx], 0.0f, 1.0f, "");
                    if (ImGui::IsItemActive() || ImGui::IsItemHovered())
                        ImGui::SetTooltip("%.3f", values2[nx]);
                    ImGui::PopID();
                }
                ImGui::EndGroup();
            }
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::PushID("set3");
            for (int i = 0; i < 4; i++)
            {
                if (i > 0) ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::PushStyleVar(ImGuiStyleVar_GrabMinSize, 40);
                ImGui::VSliderFloat("##v", ImVec2(40,160), &values[i], 0.0f, 1.0f, "%.2f\nsec");
                ImGui::PopStyleVar();
                ImGui::PopID();
            }
            ImGui::PopID();
            ImGui::PopStyleVar();
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Layout"))
    {
        if (ImGui::TreeNode("Child regions"))
        {
            static bool disable_mouse_wheel = false;
            ImGui::Checkbox("Disable Mouse Wheel", &disable_mouse_wheel);

            ImGui::Text("Without border");
            static int line = 50;
            bool goto_line = ImGui::Button("Goto");
            ImGui::SameLine();
            ImGui::PushItemWidth(100);
            goto_line |= ImGui::InputInt("##Line", &line, 0, 0, ImGuiInputTextFlags_EnterReturnsTrue);
            ImGui::PopItemWidth();

            ImGui::BeginChild("Sub1", ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f,300), false, ImGuiWindowFlags_HorizontalScrollbar | (disable_mouse_wheel ? ImGuiWindowFlags_NoScrollWithMouse : 0));
            for (int i = 0; i < 100; i++)
            {
                ImGui::Text("%04d: scrollable region", i);
                if (goto_line && line == i)
                    ImGui::SetScrollHere();
            }
            if (goto_line && line >= 100)
                ImGui::SetScrollHere();
            ImGui::EndChild();

            ImGui::SameLine();

            ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
            ImGui::BeginChild("Sub2", ImVec2(0,300), true, (disable_mouse_wheel ? ImGuiWindowFlags_NoScrollWithMouse : 0));
            ImGui::Text("With border");
            ImGui::Columns(2);
            for (int i = 0; i < 100; i++)
            {
                if (i == 50)
                    ImGui::NextColumn();
                char buf[32];
                sprintf(buf, "%08x", i*5731);
                ImGui::Button(buf, ImVec2(-1.0f, 0.0f));
            }
            ImGui::EndChild();
            ImGui::PopStyleVar();

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Widgets Width"))
        {
            static float f = 0.0f;
            ImGui::Text("PushItemWidth(100)");
            ImGui::SameLine(); ShowHelpMarker("Fixed width.");
            ImGui::PushItemWidth(100);
            ImGui::DragFloat("float##1", &f);
            ImGui::PopItemWidth();

            ImGui::Text("PushItemWidth(GetWindowWidth() * 0.5f)");
            ImGui::SameLine(); ShowHelpMarker("Half of window width.");
            ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
            ImGui::DragFloat("float##2", &f);
            ImGui::PopItemWidth();

            ImGui::Text("PushItemWidth(GetContentRegionAvailWidth() * 0.5f)");
            ImGui::SameLine(); ShowHelpMarker("Half of available width.\n(~ right-cursor_pos)\n(works within a column set)");
            ImGui::PushItemWidth(ImGui::GetContentRegionAvailWidth() * 0.5f);
            ImGui::DragFloat("float##3", &f);
            ImGui::PopItemWidth();

            ImGui::Text("PushItemWidth(-100)");
            ImGui::SameLine(); ShowHelpMarker("Align to right edge minus 100");
            ImGui::PushItemWidth(-100);
            ImGui::DragFloat("float##4", &f);
            ImGui::PopItemWidth();

            ImGui::Text("PushItemWidth(-1)");
            ImGui::SameLine(); ShowHelpMarker("Align to right edge");
            ImGui::PushItemWidth(-1);
            ImGui::DragFloat("float##5", &f);
            ImGui::PopItemWidth();

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Basic Horizontal Layout"))
        {
            ImGui::TextWrapped("(Use ImGui::SameLine() to keep adding items to the right of the preceding item)");

            // Text
            ImGui::Text("Two items: Hello"); ImGui::SameLine();
            ImGui::TextColored(ImVec4(1,1,0,1), "Sailor");

            // Adjust spacing
            ImGui::Text("More spacing: Hello"); ImGui::SameLine(0, 20);
            ImGui::TextColored(ImVec4(1,1,0,1), "Sailor");

            // Button
            ImGui::AlignTextToFramePadding();
            ImGui::Text("Normal buttons"); ImGui::SameLine();
            ImGui::Button("Banana"); ImGui::SameLine();
            ImGui::Button("Apple"); ImGui::SameLine();
            ImGui::Button("Corniflower");

            // Button
            ImGui::Text("Small buttons"); ImGui::SameLine();
            ImGui::SmallButton("Like this one"); ImGui::SameLine();
            ImGui::Text("can fit within a text block.");

            // Aligned to arbitrary position. Easy/cheap column.
            ImGui::Text("Aligned");
            ImGui::SameLine(150); ImGui::Text("x=150");
            ImGui::SameLine(300); ImGui::Text("x=300");
            ImGui::Text("Aligned");
            ImGui::SameLine(150); ImGui::SmallButton("x=150");
            ImGui::SameLine(300); ImGui::SmallButton("x=300");

            // Checkbox
            static bool c1=false,c2=false,c3=false,c4=false;
            ImGui::Checkbox("My", &c1); ImGui::SameLine();
            ImGui::Checkbox("Tailor", &c2); ImGui::SameLine();
            ImGui::Checkbox("Is", &c3); ImGui::SameLine();
            ImGui::Checkbox("Rich", &c4);

            // Various
            static float f0=1.0f, f1=2.0f, f2=3.0f;
            ImGui::PushItemWidth(80);
            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD" };
            static int item = -1;
            ImGui::Combo("Combo", &item, items, IM_ARRAYSIZE(items)); ImGui::SameLine();
            ImGui::SliderFloat("X", &f0, 0.0f,5.0f); ImGui::SameLine();
            ImGui::SliderFloat("Y", &f1, 0.0f,5.0f); ImGui::SameLine();
            ImGui::SliderFloat("Z", &f2, 0.0f,5.0f);
            ImGui::PopItemWidth();

            ImGui::PushItemWidth(80);
            ImGui::Text("Lists:");
            static int selection[4] = { 0, 1, 2, 3 };
            for (int i = 0; i < 4; i++)
            {
                if (i > 0) ImGui::SameLine();
                ImGui::PushID(i);
                ImGui::ListBox("", &selection[i], items, IM_ARRAYSIZE(items));
                ImGui::PopID();
                //if (ImGui::IsItemHovered()) ImGui::SetTooltip("ListBox %d hovered", i);
            }
            ImGui::PopItemWidth();

            // Dummy
            ImVec2 sz(30,30);
            ImGui::Button("A", sz); ImGui::SameLine();
            ImGui::Dummy(sz); ImGui::SameLine();
            ImGui::Button("B", sz);

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Groups"))
        {
            ImGui::TextWrapped("(Using ImGui::BeginGroup()/EndGroup() to layout items. BeginGroup() basically locks the horizontal position. EndGroup() bundles the whole group so that you can use functions such as IsItemHovered() on it.)");
            ImGui::BeginGroup();
            {
                ImGui::BeginGroup();
                ImGui::Button("AAA");
                ImGui::SameLine();
                ImGui::Button("BBB");
                ImGui::SameLine();
                ImGui::BeginGroup();
                ImGui::Button("CCC");
                ImGui::Button("DDD");
                ImGui::EndGroup();
                ImGui::SameLine();
                ImGui::Button("EEE");
                ImGui::EndGroup();
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("First group hovered");
            }
            // Capture the group size and create widgets using the same size
            ImVec2 size = ImGui::GetItemRectSize();
            const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
            ImGui::PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, NULL, 0.0f, 1.0f, size);

            ImGui::Button("ACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f,size.y));
            ImGui::SameLine();
            ImGui::Button("REACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f,size.y));
            ImGui::EndGroup();
            ImGui::SameLine();

            ImGui::Button("LEVERAGE\nBUZZWORD", size);
            ImGui::SameLine();

            ImGui::ListBoxHeader("List", size);
            ImGui::Selectable("Selected", true);
            ImGui::Selectable("Not Selected", false);
            ImGui::ListBoxFooter();

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Text Baseline Alignment"))
        {
            ImGui::TextWrapped("(This is testing the vertical alignment that occurs on text to keep it at the same baseline as widgets. Lines only composed of text or \"small\" widgets fit in less vertical spaces than lines with normal widgets)");

            ImGui::Text("One\nTwo\nThree"); ImGui::SameLine();
            ImGui::Text("Hello\nWorld"); ImGui::SameLine();
            ImGui::Text("Banana");

            ImGui::Text("Banana"); ImGui::SameLine();
            ImGui::Text("Hello\nWorld"); ImGui::SameLine();
            ImGui::Text("One\nTwo\nThree");

            ImGui::Button("HOP##1"); ImGui::SameLine();
            ImGui::Text("Banana"); ImGui::SameLine();
            ImGui::Text("Hello\nWorld"); ImGui::SameLine();
            ImGui::Text("Banana");

            ImGui::Button("HOP##2"); ImGui::SameLine();
            ImGui::Text("Hello\nWorld"); ImGui::SameLine();
            ImGui::Text("Banana");

            ImGui::Button("TEST##1"); ImGui::SameLine();
            ImGui::Text("TEST"); ImGui::SameLine();
            ImGui::SmallButton("TEST##2");

            ImGui::AlignTextToFramePadding(); // If your line starts with text, call this to align it to upcoming widgets.
            ImGui::Text("Text aligned to Widget"); ImGui::SameLine();
            ImGui::Button("Widget##1"); ImGui::SameLine();
            ImGui::Text("Widget"); ImGui::SameLine();
            ImGui::SmallButton("Widget##2"); ImGui::SameLine();
            ImGui::Button("Widget##3");

            // Tree
            const float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
            ImGui::Button("Button##1");
            ImGui::SameLine(0.0f, spacing);
            if (ImGui::TreeNode("Node##1")) { for (int i = 0; i < 6; i++) ImGui::BulletText("Item %d..", i); ImGui::TreePop(); }    // Dummy tree data

            ImGui::AlignTextToFramePadding();         // Vertically align text node a bit lower so it'll be vertically centered with upcoming widget. Otherwise you can use SmallButton (smaller fit).
            bool node_open = ImGui::TreeNode("Node##2");  // Common mistake to avoid: if we want to SameLine after TreeNode we need to do it before we add child content.
            ImGui::SameLine(0.0f, spacing); ImGui::Button("Button##2");
            if (node_open) { for (int i = 0; i < 6; i++) ImGui::BulletText("Item %d..", i); ImGui::TreePop(); }   // Dummy tree data

            // Bullet
            ImGui::Button("Button##3");
            ImGui::SameLine(0.0f, spacing);
            ImGui::BulletText("Bullet text");

            ImGui::AlignTextToFramePadding();
            ImGui::BulletText("Node");
            ImGui::SameLine(0.0f, spacing); ImGui::Button("Button##4");

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Scrolling"))
        {
            ImGui::TextWrapped("(Use SetScrollHere() or SetScrollFromPosY() to scroll to a given position.)");
            static bool track = true;
            static int track_line = 50, scroll_to_px = 200;
            ImGui::Checkbox("Track", &track);
            ImGui::PushItemWidth(100);
            ImGui::SameLine(130); track |= ImGui::DragInt("##line", &track_line, 0.25f, 0, 99, "Line = %.0f");
            bool scroll_to = ImGui::Button("Scroll To Pos");
            ImGui::SameLine(130); scroll_to |= ImGui::DragInt("##pos_y", &scroll_to_px, 1.00f, 0, 9999, "Y = %.0f px");
            ImGui::PopItemWidth();
            if (scroll_to) track = false;

            for (int i = 0; i < 5; i++)
            {
                if (i > 0) ImGui::SameLine();
                ImGui::BeginGroup();
                ImGui::Text("%s", i == 0 ? "Top" : i == 1 ? "25%" : i == 2 ? "Center" : i == 3 ? "75%" : "Bottom");
                ImGui::BeginChild(ImGui::GetID((void*)(intptr_t)i), ImVec2(ImGui::GetWindowWidth() * 0.17f, 200.0f), true);
                if (scroll_to)
                    ImGui::SetScrollFromPosY(ImGui::GetCursorStartPos().y + scroll_to_px, i * 0.25f);
                for (int line = 0; line < 100; line++)
                {
                    if (track && line == track_line)
                    {
                        ImGui::TextColored(ImColor(255,255,0), "Line %d", line);
                        ImGui::SetScrollHere(i * 0.25f); // 0.0f:top, 0.5f:center, 1.0f:bottom
                    }
                    else
                    {
                        ImGui::Text("Line %d", line);
                    }
                }
                float scroll_y = ImGui::GetScrollY(), scroll_max_y = ImGui::GetScrollMaxY();
                ImGui::EndChild();
                ImGui::Text("%.0f/%0.f", scroll_y, scroll_max_y);
                ImGui::EndGroup();
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Horizontal Scrolling"))
        {
            ImGui::Bullet(); ImGui::TextWrapped("Horizontal scrolling for a window has to be enabled explicitly via the ImGuiWindowFlags_HorizontalScrollbar flag.");
            ImGui::Bullet(); ImGui::TextWrapped("You may want to explicitly specify content width by calling SetNextWindowContentWidth() before Begin().");
            static int lines = 7;
            ImGui::SliderInt("Lines", &lines, 1, 15);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2.0f, 1.0f));
            ImGui::BeginChild("scrolling", ImVec2(0, ImGui::GetFrameHeightWithSpacing()*7 + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
            for (int line = 0; line < lines; line++)
            {
                // Display random stuff (for the sake of this trivial demo we are using basic Button+SameLine. If you want to create your own time line for a real application you may be better off 
                // manipulating the cursor position yourself, aka using SetCursorPos/SetCursorScreenPos to position the widgets yourself. You may also want to use the lower-level ImDrawList API)
                int num_buttons = 10 + ((line & 1) ? line * 9 : line * 3);
                for (int n = 0; n < num_buttons; n++)
                {
                    if (n > 0) ImGui::SameLine();
                    ImGui::PushID(n + line * 1000);
                    char num_buf[16];
                    sprintf(num_buf, "%d", n);
                    const char* label = (!(n%15)) ? "FizzBuzz" : (!(n%3)) ? "Fizz" : (!(n%5)) ? "Buzz" : num_buf;
                    float hue = n*0.05f;
                    ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(hue, 0.6f, 0.6f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(hue, 0.7f, 0.7f));
                    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(hue, 0.8f, 0.8f));
                    ImGui::Button(label, ImVec2(40.0f + sinf((float)(line + n)) * 20.0f, 0.0f));
                    ImGui::PopStyleColor(3);
                    ImGui::PopID();
                }
            }
            float scroll_x = ImGui::GetScrollX(), scroll_max_x = ImGui::GetScrollMaxX();
            ImGui::EndChild();
            ImGui::PopStyleVar(2);
            float scroll_x_delta = 0.0f;
            ImGui::SmallButton("<<"); if (ImGui::IsItemActive()) scroll_x_delta = -ImGui::GetIO().DeltaTime * 1000.0f; ImGui::SameLine(); 
            ImGui::Text("Scroll from code"); ImGui::SameLine();
            ImGui::SmallButton(">>"); if (ImGui::IsItemActive()) scroll_x_delta = +ImGui::GetIO().DeltaTime * 1000.0f; ImGui::SameLine(); 
            ImGui::Text("%.0f/%.0f", scroll_x, scroll_max_x);
            if (scroll_x_delta != 0.0f)
            {
                ImGui::BeginChild("scrolling"); // Demonstrate a trick: you can use Begin to set yourself in the context of another window (here we are already out of your child window)
                ImGui::SetScrollX(ImGui::GetScrollX() + scroll_x_delta);
                ImGui::End();
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Clipping"))
        {
            static ImVec2 size(100, 100), offset(50, 20);
            ImGui::TextWrapped("On a per-widget basis we are occasionally clipping text CPU-side if it won't fit in its frame. Otherwise we are doing coarser clipping + passing a scissor rectangle to the renderer. The system is designed to try minimizing both execution and CPU/GPU rendering cost.");
            ImGui::DragFloat2("size", (float*)&size, 0.5f, 0.0f, 200.0f, "%.0f");
            ImGui::TextWrapped("(Click and drag)");
            ImVec2 pos = ImGui::GetCursorScreenPos();
            ImVec4 clip_rect(pos.x, pos.y, pos.x+size.x, pos.y+size.y);
            ImGui::InvisibleButton("##dummy", size);
            if (ImGui::IsItemActive() && ImGui::IsMouseDragging()) { offset.x += ImGui::GetIO().MouseDelta.x; offset.y += ImGui::GetIO().MouseDelta.y; }
            ImGui::GetWindowDrawList()->AddRectFilled(pos, ImVec2(pos.x+size.x,pos.y+size.y), ImColor(90,90,120,255));
            ImGui::GetWindowDrawList()->AddText(ImGui::GetFont(), ImGui::GetFontSize()*2.0f, ImVec2(pos.x+offset.x,pos.y+offset.y), ImColor(255,255,255,255), "Line 1 hello\nLine 2 clip me!", NULL, 0.0f, &clip_rect);
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Popups & Modal windows"))
    {
        if (ImGui::TreeNode("Popups"))
        {
            ImGui::TextWrapped("When a popup is active, it inhibits interacting with windows that are behind the popup. Clicking outside the popup closes it.");

            static int selected_fish = -1;
            const char* names[] = { "Bream", "Haddock", "Mackerel", "Pollock", "Tilefish" };
            static bool toggles[] = { true, false, false, false, false };

            // Simple selection popup
            // (If you want to show the current selection inside the Button itself, you may want to build a string using the "###" operator to preserve a constant ID with a variable label)
            if (ImGui::Button("Select.."))
                ImGui::OpenPopup("select");
            ImGui::SameLine();
            ImGui::TextUnformatted(selected_fish == -1 ? "<None>" : names[selected_fish]);
            if (ImGui::BeginPopup("select"))
            {
                ImGui::Text("Aquarium");
                ImGui::Separator();
                for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                    if (ImGui::Selectable(names[i]))
                        selected_fish = i;
                ImGui::EndPopup();
            }

            // Showing a menu with toggles
            if (ImGui::Button("Toggle.."))
                ImGui::OpenPopup("toggle");
            if (ImGui::BeginPopup("toggle"))
            {
                for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                    ImGui::MenuItem(names[i], "", &toggles[i]);
                if (ImGui::BeginMenu("Sub-menu"))
                {
                    ImGui::MenuItem("Click me");
                    ImGui::EndMenu();
                }

                ImGui::Separator();
                ImGui::Text("Tooltip here");
                if (ImGui::IsItemHovered())
                    ImGui::SetTooltip("I am a tooltip over a popup");

                if (ImGui::Button("Stacked Popup"))
                    ImGui::OpenPopup("another popup");
                if (ImGui::BeginPopup("another popup"))
                {
                    for (int i = 0; i < IM_ARRAYSIZE(names); i++)
                        ImGui::MenuItem(names[i], "", &toggles[i]);
                    if (ImGui::BeginMenu("Sub-menu"))
                    {
                        ImGui::MenuItem("Click me");
                        ImGui::EndMenu();
                    }
                    ImGui::EndPopup();
                }
                ImGui::EndPopup();
            }

            if (ImGui::Button("Popup Menu.."))
                ImGui::OpenPopup("FilePopup");
            if (ImGui::BeginPopup("FilePopup"))
            {
                ShowExampleMenuFile();
                ImGui::EndPopup();
            }

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Context menus"))
        {
            // BeginPopupContextItem() is a helper to provide common/simple popup behavior of essentially doing:
            //    if (IsItemHovered() && IsMouseClicked(0))
            //       OpenPopup(id);
            //    return BeginPopup(id);
            // For more advanced uses you may want to replicate and cuztomize this code. This the comments inside BeginPopupContextItem() implementation.
            static float value = 0.5f;
            ImGui::Text("Value = %.3f (<-- right-click here)", value);
            if (ImGui::BeginPopupContextItem("item context menu"))
            {
                if (ImGui::Selectable("Set to zero")) value = 0.0f;
                if (ImGui::Selectable("Set to PI")) value = 3.1415f;
                ImGui::PushItemWidth(-1);
                ImGui::DragFloat("##Value", &value, 0.1f, 0.0f, 0.0f);
                ImGui::PopItemWidth();
                ImGui::EndPopup();
            }

            static char name[32] = "Label1";
            char buf[64]; sprintf(buf, "Button: %s###Button", name); // ### operator override ID ignoring the preceding label
            ImGui::Button(buf);
            if (ImGui::BeginPopupContextItem()) // When used after an item that has an ID (here the Button), we can skip providing an ID to BeginPopupContextItem().
            {
                ImGui::Text("Edit name:");
                ImGui::InputText("##edit", name, IM_ARRAYSIZE(name));
                if (ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }
            ImGui::SameLine(); ImGui::Text("(<-- right-click here)");

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Modals"))
        {
            ImGui::TextWrapped("Modal windows are like popups but the user cannot close them by clicking outside the window.");

            if (ImGui::Button("Delete.."))
                ImGui::OpenPopup("Delete?");
            if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                    ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!\n\n");
                ImGui::Separator();

                //static int dummy_i = 0;
                //ImGui::Combo("Combo", &dummy_i, "Delete\0Delete harder\0");

                static bool dont_ask_me_next_time = false;
                ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
                ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
                ImGui::PopStyleVar();

                if (ImGui::Button("OK", ImVec2(120,0))) { ImGui::CloseCurrentPopup(); }
                ImGui::SameLine();
                if (ImGui::Button("Cancel", ImVec2(120,0))) { ImGui::CloseCurrentPopup(); }
                ImGui::EndPopup();
            }

            if (ImGui::Button("Stacked modals.."))
                ImGui::OpenPopup("Stacked 1");
            if (ImGui::BeginPopupModal("Stacked 1"))
            {
                ImGui::Text("Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDarkening] for darkening.");
                static int item = 1;
                ImGui::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
                static float color[4] = { 0.4f,0.7f,0.0f,0.5f };
                ImGui::ColorEdit4("color", color);  // This is to test behavior of stacked regular popups over a modal

                if (ImGui::Button("Add another modal.."))
                    ImGui::OpenPopup("Stacked 2");
                if (ImGui::BeginPopupModal("Stacked 2"))
                {
                    ImGui::Text("Hello from Stacked The Second");
                    if (ImGui::Button("Close"))
                        ImGui::CloseCurrentPopup();
                    ImGui::EndPopup();
                }

                if (ImGui::Button("Close"))
                    ImGui::CloseCurrentPopup();
                ImGui::EndPopup();
            }

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Menus inside a regular window"))
        {
            ImGui::TextWrapped("Below we are testing adding menu items to a regular window. It's rather unusual but should work!");
            ImGui::Separator();
            // NB: As a quirk in this very specific example, we want to differentiate the parent of this menu from the parent of the various popup menus above.
            // To do so we are encloding the items in a PushID()/PopID() block to make them two different menusets. If we don't, opening any popup above and hovering our menu here
            // would open it. This is because once a menu is active, we allow to switch to a sibling menu by just hovering on it, which is the desired behavior for regular menus.
            ImGui::PushID("foo");
            ImGui::MenuItem("Menu item", "CTRL+M");
            if (ImGui::BeginMenu("Menu inside a regular window"))
            {
                ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::PopID();
            ImGui::Separator();
            ImGui::TreePop();
        }
    }

    if (ImGui::CollapsingHeader("Columns"))
    {
        ImGui::PushID("Columns");

        // Basic columns
        if (ImGui::TreeNode("Basic"))
        {
            ImGui::Text("Without border:");
            ImGui::Columns(3, "mycolumns3", false);  // 3-ways, no border
            ImGui::Separator();
            for (int n = 0; n < 14; n++)
            {
                char label[32];
                sprintf(label, "Item %d", n);
                if (ImGui::Selectable(label)) {}
                //if (ImGui::Button(label, ImVec2(-1,0))) {}
                ImGui::NextColumn();
            }
            ImGui::Columns(1);
            ImGui::Separator();

            ImGui::Text("With border:");
            ImGui::Columns(4, "mycolumns"); // 4-ways, with border
            ImGui::Separator();
            ImGui::Text("ID"); ImGui::NextColumn();
            ImGui::Text("Name"); ImGui::NextColumn();
            ImGui::Text("Path"); ImGui::NextColumn();
            ImGui::Text("Hovered"); ImGui::NextColumn();
            ImGui::Separator();
            const char* names[3] = { "One", "Two", "Three" };
            const char* paths[3] = { "/path/one", "/path/two", "/path/three" };
            static int selected = -1;
            for (int i = 0; i < 3; i++)
            {
                char label[32];
                sprintf(label, "%04d", i);
                if (ImGui::Selectable(label, selected == i, ImGuiSelectableFlags_SpanAllColumns))
                    selected = i;
                bool hovered = ImGui::IsItemHovered();
                ImGui::NextColumn();
                ImGui::Text(names[i]); ImGui::NextColumn();
                ImGui::Text(paths[i]); ImGui::NextColumn();
                ImGui::Text("%d", hovered); ImGui::NextColumn();
            }
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::TreePop();
        }

        // Create multiple items in a same cell before switching to next column
        if (ImGui::TreeNode("Mixed items"))
        {
            ImGui::Columns(3, "mixed");
            ImGui::Separator();

            ImGui::Text("Hello");
            ImGui::Button("Banana");
            ImGui::NextColumn();

            ImGui::Text("ImGui");
            ImGui::Button("Apple");
            static float foo = 1.0f;
            ImGui::InputFloat("red", &foo, 0.05f, 0, 3);
            ImGui::Text("An extra line here.");
            ImGui::NextColumn();

                ImGui::Text("Sailor");
            ImGui::Button("Corniflower");
            static float bar = 1.0f;
            ImGui::InputFloat("blue", &bar, 0.05f, 0, 3);
            ImGui::NextColumn();

            if (ImGui::CollapsingHeader("Category A")) { ImGui::Text("Blah blah blah"); } ImGui::NextColumn();
            if (ImGui::CollapsingHeader("Category B")) { ImGui::Text("Blah blah blah"); } ImGui::NextColumn();
            if (ImGui::CollapsingHeader("Category C")) { ImGui::Text("Blah blah blah"); } ImGui::NextColumn();
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::TreePop();
        }

        // Word wrapping
        if (ImGui::TreeNode("Word-wrapping"))
        {
            ImGui::Columns(2, "word-wrapping");
            ImGui::Separator();
            ImGui::TextWrapped("The quick brown fox jumps over the lazy dog.");
            ImGui::TextWrapped("Hello Left");
            ImGui::NextColumn();
            ImGui::TextWrapped("The quick brown fox jumps over the lazy dog.");
            ImGui::TextWrapped("Hello Right");
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Borders"))
        {
            // NB: Future columns API should allow automatic horizontal borders.
            static bool h_borders = true;
            static bool v_borders = true;
            ImGui::Checkbox("horizontal", &h_borders);
            ImGui::SameLine();
            ImGui::Checkbox("vertical", &v_borders);
            ImGui::Columns(4, NULL, v_borders);
            for (int i = 0; i < 4*3; i++)
            {
                if (h_borders && ImGui::GetColumnIndex() == 0)
                    ImGui::Separator();
                ImGui::Text("%c%c%c", 'a'+i, 'a'+i, 'a'+i);
                ImGui::Text("Width %.2f\nOffset %.2f", ImGui::GetColumnWidth(), ImGui::GetColumnOffset());
                ImGui::NextColumn();
            }
            ImGui::Columns(1);
            if (h_borders)
                ImGui::Separator();
            ImGui::TreePop();
        }

        // Scrolling columns
        /*
        if (ImGui::TreeNode("Vertical Scrolling"))
        {
            ImGui::BeginChild("##header", ImVec2(0, ImGui::GetTextLineHeightWithSpacing()+ImGui::GetStyle().ItemSpacing.y));
            ImGui::Columns(3);
            ImGui::Text("ID"); ImGui::NextColumn();
            ImGui::Text("Name"); ImGui::NextColumn();
            ImGui::Text("Path"); ImGui::NextColumn();
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::EndChild();
            ImGui::BeginChild("##scrollingregion", ImVec2(0, 60));
            ImGui::Columns(3);
            for (int i = 0; i < 10; i++)
            {
                ImGui::Text("%04d", i); ImGui::NextColumn();
                ImGui::Text("Foobar"); ImGui::NextColumn();
                ImGui::Text("/path/foobar/%04d/", i); ImGui::NextColumn();
            }
            ImGui::Columns(1);
            ImGui::EndChild();
            ImGui::TreePop();
        }
        */

        if (ImGui::TreeNode("Horizontal Scrolling"))
        {
            ImGui::SetNextWindowContentSize(ImVec2(1500.0f, 0.0f));
            ImGui::BeginChild("##ScrollingRegion", ImVec2(0, ImGui::GetFontSize() * 20), false, ImGuiWindowFlags_HorizontalScrollbar);
            ImGui::Columns(10);
            int ITEMS_COUNT = 2000;
            ImGuiListClipper clipper(ITEMS_COUNT);  // Also demonstrate using the clipper for large list
            while (clipper.Step())
            {
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                    for (int j = 0; j < 10; j++)
                    {
                        ImGui::Text("Line %d Column %d...", i, j);
                        ImGui::NextColumn();
                    }
            }
            ImGui::Columns(1);
            ImGui::EndChild();
            ImGui::TreePop();
        }

        bool node_open = ImGui::TreeNode("Tree within single cell");
        ImGui::SameLine(); ShowHelpMarker("NB: Tree node must be poped before ending the cell. There's no storage of state per-cell.");
        if (node_open)
        {
            ImGui::Columns(2, "tree items");
            ImGui::Separator();
            if (ImGui::TreeNode("Hello")) { ImGui::BulletText("Sailor"); ImGui::TreePop(); } ImGui::NextColumn();
            if (ImGui::TreeNode("Bonjour")) { ImGui::BulletText("Marin"); ImGui::TreePop(); } ImGui::NextColumn();
            ImGui::Columns(1);
            ImGui::Separator();
            ImGui::TreePop();
        }
        ImGui::PopID();
    }

    if (ImGui::CollapsingHeader("Filtering"))
    {
        static ImGuiTextFilter filter;
        ImGui::Text("Filter usage:\n"
                    "  \"\"         display all lines\n"
                    "  \"xxx\"      display lines containing \"xxx\"\n"
                    "  \"xxx,yyy\"  display lines containing \"xxx\" or \"yyy\"\n"
                    "  \"-xxx\"     hide lines containing \"xxx\"");
        filter.Draw();
        const char* lines[] = { "aaa1.c", "bbb1.c", "ccc1.c", "aaa2.cpp", "bbb2.cpp", "ccc2.cpp", "abc.h", "hello, world" };
        for (int i = 0; i < IM_ARRAYSIZE(lines); i++)
            if (filter.PassFilter(lines[i]))
                ImGui::BulletText("%s", lines[i]);
    }

    if (ImGui::CollapsingHeader("Inputs & Focus"))
    {
        ImGuiIO& io = ImGui::GetIO();
        ImGui::Checkbox("io.MouseDrawCursor", &io.MouseDrawCursor);
        ImGui::SameLine(); ShowHelpMarker("Request ImGui to render a mouse cursor for you in software. Note that a mouse cursor rendered via your application GPU rendering path will feel more laggy than hardware cursor, but will be more in sync with your other visuals.\n\nSome desktop applications may use both kinds of cursors (e.g. enable software cursor only when resizing/dragging something).");

        ImGui::Text("WantCaptureMouse: %d", io.WantCaptureMouse);
        ImGui::Text("WantCaptureKeyboard: %d", io.WantCaptureKeyboard);
        ImGui::Text("WantTextInput: %d", io.WantTextInput);
        ImGui::Text("WantMoveMouse: %d", io.WantMoveMouse);

        if (ImGui::TreeNode("Keyboard & Mouse State"))
        {
            if (ImGui::IsMousePosValid())
                ImGui::Text("Mouse pos: (%g, %g)", io.MousePos.x, io.MousePos.y);
            else
                ImGui::Text("Mouse pos: <INVALID>");
            ImGui::Text("Mouse down:");     for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (io.MouseDownDuration[i] >= 0.0f)   { ImGui::SameLine(); ImGui::Text("b%d (%.02f secs)", i, io.MouseDownDuration[i]); }
            ImGui::Text("Mouse clicked:");  for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseClicked(i))          { ImGui::SameLine(); ImGui::Text("b%d", i); }
            ImGui::Text("Mouse dbl-clicked:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseDoubleClicked(i)) { ImGui::SameLine(); ImGui::Text("b%d", i); }
            ImGui::Text("Mouse released:"); for (int i = 0; i < IM_ARRAYSIZE(io.MouseDown); i++) if (ImGui::IsMouseReleased(i))         { ImGui::SameLine(); ImGui::Text("b%d", i); }
            ImGui::Text("Mouse wheel: %.1f", io.MouseWheel);

            ImGui::Text("Keys down:");      for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (io.KeysDownDuration[i] >= 0.0f)     { ImGui::SameLine(); ImGui::Text("%d (%.02f secs)", i, io.KeysDownDuration[i]); }
            ImGui::Text("Keys pressed:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyPressed(i))             { ImGui::SameLine(); ImGui::Text("%d", i); }
            ImGui::Text("Keys release:");   for (int i = 0; i < IM_ARRAYSIZE(io.KeysDown); i++) if (ImGui::IsKeyReleased(i))            { ImGui::SameLine(); ImGui::Text("%d", i); }
            ImGui::Text("Keys mods: %s%s%s%s", io.KeyCtrl ? "CTRL " : "", io.KeyShift ? "SHIFT " : "", io.KeyAlt ? "ALT " : "", io.KeySuper ? "SUPER " : "");


            ImGui::Button("Hovering me sets the\nkeyboard capture flag");
            if (ImGui::IsItemHovered())
                ImGui::CaptureKeyboardFromApp(true);
            ImGui::SameLine();
            ImGui::Button("Holding me clears the\nthe keyboard capture flag");
            if (ImGui::IsItemActive())
                ImGui::CaptureKeyboardFromApp(false);

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Tabbing"))
        {
            ImGui::Text("Use TAB/SHIFT+TAB to cycle through keyboard editable fields.");
            static char buf[32] = "dummy";
            ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
            ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
            ImGui::InputText("3", buf, IM_ARRAYSIZE(buf));
            ImGui::PushAllowKeyboardFocus(false);
            ImGui::InputText("4 (tab skip)", buf, IM_ARRAYSIZE(buf));
            //ImGui::SameLine(); ShowHelperMarker("Use ImGui::PushAllowKeyboardFocus(bool)\nto disable tabbing through certain widgets.");
            ImGui::PopAllowKeyboardFocus();
            ImGui::InputText("5", buf, IM_ARRAYSIZE(buf));
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Focus from code"))
        {
            bool focus_1 = ImGui::Button("Focus on 1"); ImGui::SameLine();
            bool focus_2 = ImGui::Button("Focus on 2"); ImGui::SameLine();
            bool focus_3 = ImGui::Button("Focus on 3");
            int has_focus = 0;
            static char buf[128] = "click on a button to set focus";

            if (focus_1) ImGui::SetKeyboardFocusHere();
            ImGui::InputText("1", buf, IM_ARRAYSIZE(buf));
            if (ImGui::IsItemActive()) has_focus = 1;

            if (focus_2) ImGui::SetKeyboardFocusHere();
            ImGui::InputText("2", buf, IM_ARRAYSIZE(buf));
            if (ImGui::IsItemActive()) has_focus = 2;

            ImGui::PushAllowKeyboardFocus(false);
            if (focus_3) ImGui::SetKeyboardFocusHere();
            ImGui::InputText("3 (tab skip)", buf, IM_ARRAYSIZE(buf));
            if (ImGui::IsItemActive()) has_focus = 3;
            ImGui::PopAllowKeyboardFocus();
            if (has_focus)
                ImGui::Text("Item with focus: %d", has_focus);
            else
                ImGui::Text("Item with focus: <none>");
            ImGui::TextWrapped("Cursor & selection are preserved when refocusing last used item in code.");
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Focused & Hovered Test"))
        {
            static bool embed_all_inside_a_child_window = false;
            ImGui::Checkbox("Embed everything inside a child window (for additional testing)", &embed_all_inside_a_child_window);
            if (embed_all_inside_a_child_window)
                ImGui::BeginChild("embeddingchild", ImVec2(0, ImGui::GetFontSize() * 25), true);

            // Testing IsWindowFocused() function with its various flags (note that the flags can be combined)
            ImGui::BulletText(
                "IsWindowFocused() = %d\n"
                "IsWindowFocused(_ChildWindows) = %d\n"
                "IsWindowFocused(_ChildWindows|_RootWindow) = %d\n"
                "IsWindowFocused(_RootWindow) = %d\n",
                ImGui::IsWindowFocused(),
                ImGui::IsWindowFocused(ImGuiHoveredFlags_ChildWindows),
                ImGui::IsWindowFocused(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow),
                ImGui::IsWindowFocused(ImGuiHoveredFlags_RootWindow));

            // Testing IsWindowHovered() function with its various flags (note that the flags can be combined)
            ImGui::BulletText(
                "IsWindowHovered() = %d\n"
                "IsWindowHovered(_AllowWhenBlockedByPopup) = %d\n"
                "IsWindowHovered(_AllowWhenBlockedByActiveItem) = %d\n"
                "IsWindowHovered(_ChildWindows) = %d\n"
                "IsWindowHovered(_ChildWindows|_RootWindow) = %d\n"
                "IsWindowHovered(_RootWindow) = %d\n",
                ImGui::IsWindowHovered(),
                ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
                ImGui::IsWindowHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
                ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows),
                ImGui::IsWindowHovered(ImGuiHoveredFlags_ChildWindows | ImGuiHoveredFlags_RootWindow),
                ImGui::IsWindowHovered(ImGuiHoveredFlags_RootWindow));

            // Testing IsItemHovered() function (because BulletText is an item itself and that would affect the output of IsItemHovered, we pass all lines in a single items to shorten the code)
            ImGui::Button("ITEM");
            ImGui::BulletText(
                "IsItemHovered() = %d\n"
                "IsItemHovered(_AllowWhenBlockedByPopup) = %d\n"
                "IsItemHovered(_AllowWhenBlockedByActiveItem) = %d\n"
                "IsItemHovered(_AllowWhenOverlapped) = %d\n"
                "IsItemhovered(_RectOnly) = %d\n",
                ImGui::IsItemHovered(),
                ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByPopup),
                ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenBlockedByActiveItem),
                ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenOverlapped),
                ImGui::IsItemHovered(ImGuiHoveredFlags_RectOnly));

            ImGui::BeginChild("child", ImVec2(0,50), true);
            ImGui::Text("This is another child window for testing IsWindowHovered() flags.");
            ImGui::EndChild();

            if (embed_all_inside_a_child_window)
                EndChild();

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Dragging"))
        {
            ImGui::TextWrapped("You can use ImGui::GetMouseDragDelta(0) to query for the dragged amount on any widget.");
            for (int button = 0; button < 3; button++)
                ImGui::Text("IsMouseDragging(%d):\n  w/ default threshold: %d,\n  w/ zero threshold: %d\n  w/ large threshold: %d", 
                    button, ImGui::IsMouseDragging(button), ImGui::IsMouseDragging(button, 0.0f), ImGui::IsMouseDragging(button, 20.0f));
            ImGui::Button("Drag Me");
            if (ImGui::IsItemActive())
            {
                // Draw a line between the button and the mouse cursor
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                draw_list->PushClipRectFullScreen();
                draw_list->AddLine(ImGui::CalcItemRectClosestPoint(io.MousePos, true, -2.0f), io.MousePos, ImColor(ImGui::GetStyle().Colors[ImGuiCol_Button]), 4.0f);
                draw_list->PopClipRect();

                // Drag operations gets "unlocked" when the mouse has moved past a certain threshold (the default threshold is stored in io.MouseDragThreshold)
                // You can request a lower or higher threshold using the second parameter of IsMouseDragging() and GetMouseDragDelta()
                ImVec2 value_raw = ImGui::GetMouseDragDelta(0, 0.0f);
                ImVec2 value_with_lock_threshold = ImGui::GetMouseDragDelta(0);
                ImVec2 mouse_delta = io.MouseDelta;
                ImGui::SameLine(); ImGui::Text("Raw (%.1f, %.1f), WithLockThresold (%.1f, %.1f), MouseDelta (%.1f, %.1f)", value_raw.x, value_raw.y, value_with_lock_threshold.x, value_with_lock_threshold.y, mouse_delta.x, mouse_delta.y);
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("Mouse cursors"))
        {
            const char* mouse_cursors_names[] = { "Arrow", "TextInput", "Move", "ResizeNS", "ResizeEW", "ResizeNESW", "ResizeNWSE" };
            IM_ASSERT(IM_ARRAYSIZE(mouse_cursors_names) == ImGuiMouseCursor_Count_);

            ImGui::Text("Current mouse cursor = %d: %s", ImGui::GetMouseCursor(), mouse_cursors_names[ImGui::GetMouseCursor()]);
            ImGui::Text("Hover to see mouse cursors:");
            ImGui::SameLine(); ShowHelpMarker("Your application can render a different mouse cursor based on what ImGui::GetMouseCursor() returns. If software cursor rendering (io.MouseDrawCursor) is set ImGui will draw the right cursor for you, otherwise your backend needs to handle it.");
            for (int i = 0; i < ImGuiMouseCursor_Count_; i++)
            {
                char label[32];
                sprintf(label, "Mouse cursor %d: %s", i, mouse_cursors_names[i]);
                ImGui::Bullet(); ImGui::Selectable(label, false);
                if (ImGui::IsItemHovered())
                    ImGui::SetMouseCursor(i);
            }
            ImGui::TreePop();
        }
    }

    ImGui::End();
}

// Demo helper function to select among default colors. See ShowStyleEditor() for more advanced options.
// Here we use the simplified Combo() api that packs items into a single literal string. Useful for quick combo boxes where the choices are known locally.
bool ImGui::ShowStyleSelector(const char* label)
{
    static int style_idx = 0;
    if (ImGui::Combo(label, &style_idx, "Classic\0Dark\0Light\0"))
    {
        switch (style_idx)
        {
        case 0: ImGui::StyleColorsClassic(); break;
        case 1: ImGui::StyleColorsDark(); break;
        case 2: ImGui::StyleColorsLight(); break;
        }
        return true;
    }
    return false;
}

// Demo helper function to select among loaded fonts.
// Here we use the regular BeginCombo()/EndCombo() api which is more the more flexible one.
void ImGui::ShowFontSelector(const char* label)
{
    ImGuiIO& io = ImGui::GetIO();
    ImFont* font_current = ImGui::GetFont();
    if (ImGui::BeginCombo(label, font_current->GetDebugName()))
    {
        for (int n = 0; n < io.Fonts->Fonts.Size; n++)
            if (ImGui::Selectable(io.Fonts->Fonts[n]->GetDebugName(), io.Fonts->Fonts[n] == font_current))
                io.FontDefault = io.Fonts->Fonts[n];
        ImGui::EndCombo();
    }
    ImGui::SameLine(); 
    ShowHelpMarker(
        "- Load additional fonts with io.Fonts->AddFontFromFileTTF().\n"
        "- The font atlas is built when calling io.Fonts->GetTexDataAsXXXX() or io.Fonts->Build().\n"
        "- Read FAQ and documentation in extra_fonts/ for more details.\n"
        "- If you need to add/remove fonts at runtime (e.g. for DPI change), do it before calling NewFrame().");
}

void ImGui::ShowStyleEditor(ImGuiStyle* ref)
{
    // You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
    ImGuiStyle& style = ImGui::GetStyle();
    static ImGuiStyle ref_saved_style;

    // Default to using internal storage as reference
    static bool init = true;
    if (init && ref == NULL)
        ref_saved_style = style;
    init = false;
    if (ref == NULL)
        ref = &ref_saved_style;

    ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.50f);

    if (ImGui::ShowStyleSelector("Colors##Selector"))
        ref_saved_style = style;
    ImGui::ShowFontSelector("Fonts##Selector");

    // Simplified Settings
    if (ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f")) 
        style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
    { bool window_border = (style.WindowBorderSize > 0.0f); if (ImGui::Checkbox("WindowBorder", &window_border)) style.WindowBorderSize = window_border ? 1.0f : 0.0f; }
    ImGui::SameLine();
    { bool frame_border = (style.FrameBorderSize > 0.0f); if (ImGui::Checkbox("FrameBorder", &frame_border)) style.FrameBorderSize = frame_border ? 1.0f : 0.0f; }
    ImGui::SameLine();
    { bool popup_border = (style.PopupBorderSize > 0.0f); if (ImGui::Checkbox("PopupBorder", &popup_border)) style.PopupBorderSize = popup_border ? 1.0f : 0.0f; }

    // Save/Revert button
    if (ImGui::Button("Save Ref"))
        *ref = ref_saved_style = style;
    ImGui::SameLine();
    if (ImGui::Button("Revert Ref"))
        style = *ref;
    ImGui::SameLine();
    ShowHelpMarker("Save/Revert in local non-persistent storage. Default Colors definition are not affected. Use \"Export Colors\" below to save them somewhere.");

    if (ImGui::TreeNode("Rendering"))
    {
        ImGui::Checkbox("Anti-aliased lines", &style.AntiAliasedLines); ImGui::SameLine(); ShowHelpMarker("When disabling anti-aliasing lines, you'll probably want to disable borders in your style as well.");
        ImGui::Checkbox("Anti-aliased fill", &style.AntiAliasedFill);
        ImGui::PushItemWidth(100);
        ImGui::DragFloat("Curve Tessellation Tolerance", &style.CurveTessellationTol, 0.02f, 0.10f, FLT_MAX, NULL, 2.0f);
        if (style.CurveTessellationTol < 0.0f) style.CurveTessellationTol = 0.10f;
        ImGui::DragFloat("Global Alpha", &style.Alpha, 0.005f, 0.20f, 1.0f, "%.2f"); // Not exposing zero here so user doesn't "lose" the UI (zero alpha clips all widgets). But application code could have a toggle to switch between zero and non-zero.
        ImGui::PopItemWidth();
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Settings"))
    {
        ImGui::SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
        ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 16.0f, "%.0f");
        ImGui::SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
        ImGui::SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
        ImGui::SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
        ImGui::SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
        ImGui::SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
        ImGui::SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
        ImGui::SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
        ImGui::Text("BorderSize");
        ImGui::SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
        ImGui::SliderFloat("ChildBorderSize", &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
        ImGui::SliderFloat("PopupBorderSize", &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
        ImGui::SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
        ImGui::Text("Rounding");
        ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 14.0f, "%.0f");
        ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 16.0f, "%.0f");
        ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
        ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
        ImGui::Text("Alignment");
        ImGui::SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
        ImGui::SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f"); ImGui::SameLine(); ShowHelpMarker("Alignment applies when a button is larger than its text content.");
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("Colors"))
    {
        static int output_dest = 0;
        static bool output_only_modified = true;
        if (ImGui::Button("Export Unsaved"))
        {
            if (output_dest == 0)
                ImGui::LogToClipboard();
            else
                ImGui::LogToTTY();
            ImGui::LogText("ImVec4* colors = ImGui::GetStyle().Colors;" IM_NEWLINE);
            for (int i = 0; i < ImGuiCol_COUNT; i++)
            {
                const ImVec4& col = style.Colors[i];
                const char* name = ImGui::GetStyleColorName(i);
                if (!output_only_modified || memcmp(&col, &ref->Colors[i], sizeof(ImVec4)) != 0)
                    ImGui::LogText("colors[ImGuiCol_%s]%*s= ImVec4(%.2ff, %.2ff, %.2ff, %.2ff);" IM_NEWLINE, name, 23-(int)strlen(name), "", col.x, col.y, col.z, col.w);
            }
            ImGui::LogFinish();
        }
        ImGui::SameLine(); ImGui::PushItemWidth(120); ImGui::Combo("##output_type", &output_dest, "To Clipboard\0To TTY\0"); ImGui::PopItemWidth();
        ImGui::SameLine(); ImGui::Checkbox("Only Modified Colors", &output_only_modified);

        ImGui::Text("Tip: Left-click on colored square to open color picker,\nRight-click to open edit options menu.");

        static ImGuiTextFilter filter;
        filter.Draw("Filter colors", 200);

        static ImGuiColorEditFlags alpha_flags = 0;
        ImGui::RadioButton("Opaque", &alpha_flags, 0); ImGui::SameLine(); 
        ImGui::RadioButton("Alpha", &alpha_flags, ImGuiColorEditFlags_AlphaPreview); ImGui::SameLine(); 
        ImGui::RadioButton("Both", &alpha_flags, ImGuiColorEditFlags_AlphaPreviewHalf);

        ImGui::BeginChild("#colors", ImVec2(0, 300), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar);
        ImGui::PushItemWidth(-160);
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ImGui::GetStyleColorName(i);
            if (!filter.PassFilter(name))
                continue;
            ImGui::PushID(i);
            ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
            if (memcmp(&style.Colors[i], &ref->Colors[i], sizeof(ImVec4)) != 0)
            {
                // Tips: in a real user application, you may want to merge and use an icon font into the main font, so instead of "Save"/"Revert" you'd use icons.
                // Read the FAQ and extra_fonts/README.txt about using icon fonts. It's really easy and super convenient!
                ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Save")) ref->Colors[i] = style.Colors[i];
                ImGui::SameLine(0.0f, style.ItemInnerSpacing.x); if (ImGui::Button("Revert")) style.Colors[i] = ref->Colors[i];
            }
            ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
            ImGui::TextUnformatted(name);
            ImGui::PopID();
        }
        ImGui::PopItemWidth();
        ImGui::EndChild();

        ImGui::TreePop();
    }

    bool fonts_opened = ImGui::TreeNode("Fonts", "Fonts (%d)", ImGui::GetIO().Fonts->Fonts.Size);
    if (fonts_opened)
    {
        ImFontAtlas* atlas = ImGui::GetIO().Fonts;
        if (ImGui::TreeNode("Atlas texture", "Atlas texture (%dx%d pixels)", atlas->TexWidth, atlas->TexHeight))
        {
            ImGui::Image(atlas->TexID, ImVec2((float)atlas->TexWidth, (float)atlas->TexHeight), ImVec2(0,0), ImVec2(1,1), ImColor(255,255,255,255), ImColor(255,255,255,128));
            ImGui::TreePop();
        }
        ImGui::PushItemWidth(100);
        for (int i = 0; i < atlas->Fonts.Size; i++)
        {
            ImFont* font = atlas->Fonts[i];
            ImGui::PushID(font);
            bool font_details_opened = ImGui::TreeNode(font, "Font %d: \'%s\', %.2f px, %d glyphs", i, font->ConfigData ? font->ConfigData[0].Name : "", font->FontSize, font->Glyphs.Size);
            ImGui::SameLine(); if (ImGui::SmallButton("Set as default")) ImGui::GetIO().FontDefault = font;
            if (font_details_opened)
            {
                ImGui::PushFont(font);
                ImGui::Text("The quick brown fox jumps over the lazy dog");
                ImGui::PopFont();
                ImGui::DragFloat("Font scale", &font->Scale, 0.005f, 0.3f, 2.0f, "%.1f");   // Scale only this font
                ImGui::SameLine(); ShowHelpMarker("Note than the default embedded font is NOT meant to be scaled.\n\nFont are currently rendered into bitmaps at a given size at the time of building the atlas. You may oversample them to get some flexibility with scaling. You can also render at multiple sizes and select which one to use at runtime.\n\n(Glimmer of hope: the atlas system should hopefully be rewritten in the future to make scaling more natural and automatic.)");
                ImGui::Text("Ascent: %f, Descent: %f, Height: %f", font->Ascent, font->Descent, font->Ascent - font->Descent);
                ImGui::Text("Fallback character: '%c' (%d)", font->FallbackChar, font->FallbackChar);
                ImGui::Text("Texture surface: %d pixels (approx) ~ %dx%d", font->MetricsTotalSurface, (int)sqrtf((float)font->MetricsTotalSurface), (int)sqrtf((float)font->MetricsTotalSurface));
                for (int config_i = 0; config_i < font->ConfigDataCount; config_i++)
                {
                    ImFontConfig* cfg = &font->ConfigData[config_i];
                    ImGui::BulletText("Input %d: \'%s\', Oversample: (%d,%d), PixelSnapH: %d", config_i, cfg->Name, cfg->OversampleH, cfg->OversampleV, cfg->PixelSnapH);
                }
                if (ImGui::TreeNode("Glyphs", "Glyphs (%d)", font->Glyphs.Size))
                {
                    // Display all glyphs of the fonts in separate pages of 256 characters
                    const ImFontGlyph* glyph_fallback = font->FallbackGlyph; // Forcefully/dodgily make FindGlyph() return NULL on fallback, which isn't the default behavior.
                    font->FallbackGlyph = NULL;
                    for (int base = 0; base < 0x10000; base += 256)
                    {
                        int count = 0;
                        for (int n = 0; n < 256; n++)
                            count += font->FindGlyph((ImWchar)(base + n)) ? 1 : 0;
                        if (count > 0 && ImGui::TreeNode((void*)(intptr_t)base, "U+%04X..U+%04X (%d %s)", base, base+255, count, count > 1 ? "glyphs" : "glyph"))
                        {
                            float cell_spacing = style.ItemSpacing.y;
                            ImVec2 cell_size(font->FontSize * 1, font->FontSize * 1);
                            ImVec2 base_pos = ImGui::GetCursorScreenPos();
                            ImDrawList* draw_list = ImGui::GetWindowDrawList();
                            for (int n = 0; n < 256; n++)
                            {
                                ImVec2 cell_p1(base_pos.x + (n % 16) * (cell_size.x + cell_spacing), base_pos.y + (n / 16) * (cell_size.y + cell_spacing));
                                ImVec2 cell_p2(cell_p1.x + cell_size.x, cell_p1.y + cell_size.y);
                                const ImFontGlyph* glyph = font->FindGlyph((ImWchar)(base+n));;
                                draw_list->AddRect(cell_p1, cell_p2, glyph ? IM_COL32(255,255,255,100) : IM_COL32(255,255,255,50));
                                font->RenderChar(draw_list, cell_size.x, cell_p1, ImGui::GetColorU32(ImGuiCol_Text), (ImWchar)(base+n)); // We use ImFont::RenderChar as a shortcut because we don't have UTF-8 conversion functions available to generate a string.
                                if (glyph && ImGui::IsMouseHoveringRect(cell_p1, cell_p2))
                                {
                                    ImGui::BeginTooltip();
                                    ImGui::Text("Codepoint: U+%04X", base+n);
                                    ImGui::Separator();
                                    ImGui::Text("AdvanceX: %.1f", glyph->AdvanceX);
                                    ImGui::Text("Pos: (%.2f,%.2f)->(%.2f,%.2f)", glyph->X0, glyph->Y0, glyph->X1, glyph->Y1);
                                    ImGui::Text("UV: (%.3f,%.3f)->(%.3f,%.3f)", glyph->U0, glyph->V0, glyph->U1, glyph->V1);
                                    ImGui::EndTooltip();
                                }
                            }
                            ImGui::Dummy(ImVec2((cell_size.x + cell_spacing) * 16, (cell_size.y + cell_spacing) * 16));
                            ImGui::TreePop();
                        }
                    }
                    font->FallbackGlyph = glyph_fallback;
                    ImGui::TreePop();
                }
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
        static float window_scale = 1.0f;
        ImGui::DragFloat("this window scale", &window_scale, 0.005f, 0.3f, 2.0f, "%.1f");              // scale only this window
        ImGui::DragFloat("global scale", &ImGui::GetIO().FontGlobalScale, 0.005f, 0.3f, 2.0f, "%.1f"); // scale everything
        ImGui::PopItemWidth();
        ImGui::SetWindowFontScale(window_scale);
        ImGui::TreePop();
    }

    ImGui::PopItemWidth();
}

// Demonstrate creating a fullscreen menu bar and populating it.
static void ShowExampleAppMainMenuBar()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            ShowExampleMenuFile();
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Edit"))
        {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {}
            if (ImGui::MenuItem("Copy", "CTRL+C")) {}
            if (ImGui::MenuItem("Paste", "CTRL+V")) {}
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

static void ShowExampleMenuFile()
{
    ImGui::MenuItem("(dummy menu)", NULL, false, false);
    if (ImGui::MenuItem("New")) {}
    if (ImGui::MenuItem("Open", "Ctrl+O")) {}
    if (ImGui::BeginMenu("Open Recent"))
    {
        ImGui::MenuItem("fish_hat.c");
        ImGui::MenuItem("fish_hat.inl");
        ImGui::MenuItem("fish_hat.h");
        if (ImGui::BeginMenu("More.."))
        {
            ImGui::MenuItem("Hello");
            ImGui::MenuItem("Sailor");
            if (ImGui::BeginMenu("Recurse.."))
            {
                ShowExampleMenuFile();
                ImGui::EndMenu();
            }
            ImGui::EndMenu();
        }
        ImGui::EndMenu();
    }
    if (ImGui::MenuItem("Save", "Ctrl+S")) {}
    if (ImGui::MenuItem("Save As..")) {}
    ImGui::Separator();
    if (ImGui::BeginMenu("Options"))
    {
        static bool enabled = true;
        ImGui::MenuItem("Enabled", "", &enabled);
        ImGui::BeginChild("child", ImVec2(0, 60), true);
        for (int i = 0; i < 10; i++)
            ImGui::Text("Scrolling Text %d", i);
        ImGui::EndChild();
        static float f = 0.5f;
        static int n = 0;
        static bool b = true;
        ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
        ImGui::InputFloat("Input", &f, 0.1f);
        ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
        ImGui::Checkbox("Check", &b);
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Colors"))
    {
        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
        for (int i = 0; i < ImGuiCol_COUNT; i++)
        {
            const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
            ImGui::ColorButton(name, ImGui::GetStyleColorVec4((ImGuiCol)i));
            ImGui::SameLine();
            ImGui::MenuItem(name);
        }
        ImGui::PopStyleVar();
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Disabled", false)) // Disabled
    {
        IM_ASSERT(0);
    }
    if (ImGui::MenuItem("Checked", NULL, true)) {}
    if (ImGui::MenuItem("Quit", "Alt+F4")) {}
}

// Demonstrate creating a window which gets auto-resized according to its content.
static void ShowExampleAppAutoResize(bool* p_open)
{
    if (!ImGui::Begin("Example: Auto-resizing window", p_open, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::End();
        return;
    }

    static int lines = 10;
    ImGui::Text("Window will resize every-frame to the size of its content.\nNote that you probably don't want to query the window size to\noutput your content because that would create a feedback loop.");
    ImGui::SliderInt("Number of lines", &lines, 1, 20);
    for (int i = 0; i < lines; i++)
        ImGui::Text("%*sThis is line %d", i*4, "", i); // Pad with space to extend size horizontally
    ImGui::End();
}

// Demonstrate creating a window with custom resize constraints.
static void ShowExampleAppConstrainedResize(bool* p_open)
{
    struct CustomConstraints // Helper functions to demonstrate programmatic constraints
    {
        static void Square(ImGuiSizeConstraintCallbackData* data) { data->DesiredSize = ImVec2(IM_MAX(data->DesiredSize.x, data->DesiredSize.y), IM_MAX(data->DesiredSize.x, data->DesiredSize.y)); }
        static void Step(ImGuiSizeConstraintCallbackData* data)   { float step = (float)(int)(intptr_t)data->UserData; data->DesiredSize = ImVec2((int)(data->DesiredSize.x / step + 0.5f) * step, (int)(data->DesiredSize.y / step + 0.5f) * step); }
    };

    static bool auto_resize = false;
    static int type = 0;
    static int display_lines = 10;
    if (type == 0) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 0),    ImVec2(-1, FLT_MAX));      // Vertical only
    if (type == 1) ImGui::SetNextWindowSizeConstraints(ImVec2(0, -1),    ImVec2(FLT_MAX, -1));      // Horizontal only
    if (type == 2) ImGui::SetNextWindowSizeConstraints(ImVec2(100, 100), ImVec2(FLT_MAX, FLT_MAX)); // Width > 100, Height > 100
    if (type == 3) ImGui::SetNextWindowSizeConstraints(ImVec2(400, -1),  ImVec2(500, -1));          // Width 400-500
    if (type == 4) ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 400),  ImVec2(-1, 500));          // Height 400-500
    if (type == 5) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0),     ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Square);          // Always Square
    if (type == 6) ImGui::SetNextWindowSizeConstraints(ImVec2(0, 0),     ImVec2(FLT_MAX, FLT_MAX), CustomConstraints::Step, (void*)100);// Fixed Step

    ImGuiWindowFlags flags = auto_resize ? ImGuiWindowFlags_AlwaysAutoResize : 0;
    if (ImGui::Begin("Example: Constrained Resize", p_open, flags))
    {
        const char* desc[] = 
        {
            "Resize vertical only",
            "Resize horizontal only",
            "Width > 100, Height > 100",
            "Width 400-500",
            "Height 400-500",
            "Custom: Always Square",
            "Custom: Fixed Steps (100)",
        };
        if (ImGui::Button("200x200")) { ImGui::SetWindowSize(ImVec2(200, 200)); } ImGui::SameLine();
        if (ImGui::Button("500x500")) { ImGui::SetWindowSize(ImVec2(500, 500)); } ImGui::SameLine();
        if (ImGui::Button("800x200")) { ImGui::SetWindowSize(ImVec2(800, 200)); }
        ImGui::PushItemWidth(200);
        ImGui::Combo("Constraint", &type, desc, IM_ARRAYSIZE(desc));
        ImGui::DragInt("Lines", &display_lines, 0.2f, 1, 100);
        ImGui::PopItemWidth();
        ImGui::Checkbox("Auto-resize", &auto_resize);
        for (int i = 0; i < display_lines; i++)
            ImGui::Text("%*sHello, sailor! Making this line long enough for the example.", i * 4, "");
    }
    ImGui::End();
}

// Demonstrate creating a simple static window with no decoration + a context-menu to choose which corner of the screen to use.
static void ShowExampleAppFixedOverlay(bool* p_open)
{
    const float DISTANCE = 10.0f;
    static int corner = 0;
    ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
    ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.3f)); // Transparent background
    if (ImGui::Begin("Example: Fixed Overlay", p_open, ImGuiWindowFlags_NoTitleBar|ImGuiWindowFlags_NoResize|ImGuiWindowFlags_AlwaysAutoResize|ImGuiWindowFlags_NoMove|ImGuiWindowFlags_NoSavedSettings))
    {
        ImGui::Text("Simple overlay\nin the corner of the screen.\n(right-click to change position)");
        ImGui::Separator();
        ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::MenuItem("Top-left", NULL, corner == 0)) corner = 0;
            if (ImGui::MenuItem("Top-right", NULL, corner == 1)) corner = 1;
            if (ImGui::MenuItem("Bottom-left", NULL, corner == 2)) corner = 2;
            if (ImGui::MenuItem("Bottom-right", NULL, corner == 3)) corner = 3;
            ImGui::EndPopup();
        }
        ImGui::End();
    }
    ImGui::PopStyleColor();
}

// Demonstrate using "##" and "###" in identifiers to manipulate ID generation.
// This apply to regular items as well. Read FAQ section "How can I have multiple widgets with the same label? Can I have widget without a label? (Yes). A primer on the purpose of labels/IDs." for details.
static void ShowExampleAppWindowTitles(bool*)
{
    // By default, Windows are uniquely identified by their title.
    // You can use the "##" and "###" markers to manipulate the display/ID.

    // Using "##" to display same title but have unique identifier.
    ImGui::SetNextWindowPos(ImVec2(100,100), ImGuiCond_FirstUseEver);
    ImGui::Begin("Same title as another window##1");
    ImGui::Text("This is window 1.\nMy title is the same as window 2, but my identifier is unique.");
    ImGui::End();

    ImGui::SetNextWindowPos(ImVec2(100,200), ImGuiCond_FirstUseEver);
    ImGui::Begin("Same title as another window##2");
    ImGui::Text("This is window 2.\nMy title is the same as window 1, but my identifier is unique.");
    ImGui::End();

    // Using "###" to display a changing title but keep a static identifier "AnimatedTitle"
    char buf[128];
    sprintf(buf, "Animated title %c %d###AnimatedTitle", "|/-\\"[(int)(ImGui::GetTime()/0.25f)&3], ImGui::GetFrameCount());
    ImGui::SetNextWindowPos(ImVec2(100,300), ImGuiCond_FirstUseEver);
    ImGui::Begin(buf);
    ImGui::Text("This window has a changing title.");
    ImGui::End();
}

// Demonstrate using the low-level ImDrawList to draw custom shapes. 
static void ShowExampleAppCustomRendering(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(350,560), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Example: Custom rendering", p_open))
    {
        ImGui::End();
        return;
    }

    // Tip: If you do a lot of custom rendering, you probably want to use your own geometrical types and benefit of overloaded operators, etc.
    // Define IM_VEC2_CLASS_EXTRA in imconfig.h to create implicit conversions between your types and ImVec2/ImVec4.
    // ImGui defines overloaded operators but they are internal to imgui.cpp and not exposed outside (to avoid messing with your types)
    // In this example we are not using the maths operators!
    ImDrawList* draw_list = ImGui::GetWindowDrawList();

    // Primitives
    ImGui::Text("Primitives");
    static float sz = 36.0f;
    static ImVec4 col = ImVec4(1.0f,1.0f,0.4f,1.0f);
    ImGui::DragFloat("Size", &sz, 0.2f, 2.0f, 72.0f, "%.0f");
    ImGui::ColorEdit3("Color", &col.x);
    {
        const ImVec2 p = ImGui::GetCursorScreenPos();
        const ImU32 col32 = ImColor(col);
        float x = p.x + 4.0f, y = p.y + 4.0f, spacing = 8.0f;
        for (int n = 0; n < 2; n++)
        {
            float thickness = (n == 0) ? 1.0f : 4.0f;
            draw_list->AddCircle(ImVec2(x+sz*0.5f, y+sz*0.5f), sz*0.5f, col32, 20, thickness); x += sz+spacing;
            draw_list->AddRect(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, 0.0f, ImDrawCornerFlags_All, thickness); x += sz+spacing;
            draw_list->AddRect(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, 10.0f, ImDrawCornerFlags_All, thickness); x += sz+spacing;
            draw_list->AddRect(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, 10.0f, ImDrawCornerFlags_TopLeft|ImDrawCornerFlags_BotRight, thickness); x += sz+spacing;
            draw_list->AddTriangle(ImVec2(x+sz*0.5f, y), ImVec2(x+sz,y+sz-0.5f), ImVec2(x,y+sz-0.5f), col32, thickness); x += sz+spacing;
            draw_list->AddLine(ImVec2(x, y), ImVec2(x+sz, y   ), col32, thickness); x += sz+spacing;
            draw_list->AddLine(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, thickness); x += sz+spacing;
            draw_list->AddLine(ImVec2(x, y), ImVec2(x,    y+sz), col32, thickness); x += spacing;
            draw_list->AddBezierCurve(ImVec2(x, y), ImVec2(x+sz*1.3f,y+sz*0.3f), ImVec2(x+sz-sz*1.3f,y+sz-sz*0.3f), ImVec2(x+sz, y+sz), col32, thickness);
            x = p.x + 4;
            y += sz+spacing;
        }
        draw_list->AddCircleFilled(ImVec2(x+sz*0.5f, y+sz*0.5f), sz*0.5f, col32, 32); x += sz+spacing;
        draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x+sz, y+sz), col32); x += sz+spacing;
        draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, 10.0f); x += sz+spacing;
        draw_list->AddRectFilled(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, 10.0f, ImDrawCornerFlags_TopLeft|ImDrawCornerFlags_BotRight); x += sz+spacing;
        draw_list->AddTriangleFilled(ImVec2(x+sz*0.5f, y), ImVec2(x+sz,y+sz-0.5f), ImVec2(x,y+sz-0.5f), col32); x += sz+spacing;
        draw_list->AddRectFilledMultiColor(ImVec2(x, y), ImVec2(x+sz, y+sz), ImColor(0,0,0), ImColor(255,0,0), ImColor(255,255,0), ImColor(0,255,0));
        ImGui::Dummy(ImVec2((sz+spacing)*8, (sz+spacing)*3));
    }
    ImGui::Separator();
    {
        static ImVector<ImVec2> points;
        static bool adding_line = false;
        ImGui::Text("Canvas example");
        if (ImGui::Button("Clear")) points.clear();
        if (points.Size >= 2) { ImGui::SameLine(); if (ImGui::Button("Undo")) { points.pop_back(); points.pop_back(); } }
        ImGui::Text("Left-click and drag to add lines,\nRight-click to undo");

        // Here we are using InvisibleButton() as a convenience to 1) advance the cursor and 2) allows us to use IsItemHovered()
        // However you can draw directly and poll mouse/keyboard by yourself. You can manipulate the cursor using GetCursorPos() and SetCursorPos().
        // If you only use the ImDrawList API, you can notify the owner window of its extends by using SetCursorPos(max).
        ImVec2 canvas_pos = ImGui::GetCursorScreenPos();            // ImDrawList API uses screen coordinates!
        ImVec2 canvas_size = ImGui::GetContentRegionAvail();        // Resize canvas to what's available
        if (canvas_size.x < 50.0f) canvas_size.x = 50.0f;
        if (canvas_size.y < 50.0f) canvas_size.y = 50.0f;
        draw_list->AddRectFilledMultiColor(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), ImColor(50,50,50), ImColor(50,50,60), ImColor(60,60,70), ImColor(50,50,60));
        draw_list->AddRect(canvas_pos, ImVec2(canvas_pos.x + canvas_size.x, canvas_pos.y + canvas_size.y), ImColor(255,255,255));

        bool adding_preview = false;
        ImGui::InvisibleButton("canvas", canvas_size);
        ImVec2 mouse_pos_in_canvas = ImVec2(ImGui::GetIO().MousePos.x - canvas_pos.x, ImGui::GetIO().MousePos.y - canvas_pos.y);
        if (adding_line)
        {
            adding_preview = true;
            points.push_back(mouse_pos_in_canvas);
            if (!ImGui::GetIO().MouseDown[0])
                adding_line = adding_preview = false;
        }
        if (ImGui::IsItemHovered())
        {
            if (!adding_line && ImGui::IsMouseClicked(0))
            {
                points.push_back(mouse_pos_in_canvas);
                adding_line = true;
            }
            if (ImGui::IsMouseClicked(1) && !points.empty())
            {
                adding_line = adding_preview = false;
                points.pop_back();
                points.pop_back();
            }
        }
        draw_list->PushClipRect(canvas_pos, ImVec2(canvas_pos.x+canvas_size.x, canvas_pos.y+canvas_size.y), true);      // clip lines within the canvas (if we resize it, etc.)
        for (int i = 0; i < points.Size - 1; i += 2)
            draw_list->AddLine(ImVec2(canvas_pos.x + points[i].x, canvas_pos.y + points[i].y), ImVec2(canvas_pos.x + points[i+1].x, canvas_pos.y + points[i+1].y), IM_COL32(255,255,0,255), 2.0f);
        draw_list->PopClipRect();
        if (adding_preview)
            points.pop_back();
    }
    ImGui::End();
}

// Demonstrating creating a simple console window, with scrolling, filtering, completion and history.
// For the console example, here we are using a more C++ like approach of declaring a class to hold the data and the functions.
struct ExampleAppConsole
{
    char                  InputBuf[256];
    ImVector<char*>       Items;
    bool                  ScrollToBottom;
    ImVector<char*>       History;
    int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
    ImVector<const char*> Commands;

    ExampleAppConsole()
    {
        ClearLog();
        memset(InputBuf, 0, sizeof(InputBuf));
        HistoryPos = -1;
        Commands.push_back("HELP");
        Commands.push_back("HISTORY");
        Commands.push_back("CLEAR");
        Commands.push_back("CLASSIFY");  // "classify" is here to provide an example of "C"+[tab] completing to "CL" and displaying matches.
        AddLog("Welcome to ImGui!");
    }
    ~ExampleAppConsole()
    {
        ClearLog();
        for (int i = 0; i < History.Size; i++)
            free(History[i]);
    }

    // Portable helpers
    static int   Stricmp(const char* str1, const char* str2)         { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
    static int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
    static char* Strdup(const char *str)                             { size_t len = strlen(str) + 1; void* buff = malloc(len); return (char*)memcpy(buff, (const void*)str, len); }

    void    ClearLog()
    {
        for (int i = 0; i < Items.Size; i++)
            free(Items[i]);
        Items.clear();
        ScrollToBottom = true;
    }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        // FIXME-OPT
        char buf[1024];
        va_list args;
        va_start(args, fmt);
        vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
        buf[IM_ARRAYSIZE(buf)-1] = 0;
        va_end(args);
        Items.push_back(Strdup(buf));
        ScrollToBottom = true;
    }

    void    Draw(const char* title, bool* p_open)
    {
        ImGui::SetNextWindowSize(ImVec2(520,600), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(title, p_open))
        {
            ImGui::End();
            return;
        }

        // As a specific feature guaranteed by the library, after calling Begin() the last Item represent the title bar. So e.g. IsItemHovered() will return true when hovering the title bar.
        // Here we create a context menu only available from the title bar.
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Close"))
                *p_open = false;
            ImGui::EndPopup();
        }

        ImGui::TextWrapped("This example implements a console with basic coloring, completion and history. A more elaborate implementation may want to store entries along with extra data such as timestamp, emitter, etc.");
        ImGui::TextWrapped("Enter 'HELP' for help, press TAB to use text completion.");

        // TODO: display items starting from the bottom

        if (ImGui::SmallButton("Add Dummy Text")) { AddLog("%d some text", Items.Size); AddLog("some more text"); AddLog("display very important message here!"); } ImGui::SameLine();
        if (ImGui::SmallButton("Add Dummy Error")) { AddLog("[error] something went wrong"); } ImGui::SameLine();
        if (ImGui::SmallButton("Clear")) { ClearLog(); } ImGui::SameLine();
        bool copy_to_clipboard = ImGui::SmallButton("Copy"); ImGui::SameLine();
        if (ImGui::SmallButton("Scroll to bottom")) ScrollToBottom = true;
        //static float t = 0.0f; if (ImGui::GetTime() - t > 0.02f) { t = ImGui::GetTime(); AddLog("Spam %f", t); }

        ImGui::Separator();

        ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0,0));
        static ImGuiTextFilter filter;
        filter.Draw("Filter (\"incl,-excl\") (\"error\")", 180);
        ImGui::PopStyleVar();
        ImGui::Separator();

        const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear")) ClearLog();
            ImGui::EndPopup();
        }

        // Display every line as a separate entry so we can change their color or add custom widgets. If you only want raw text you can use ImGui::TextUnformatted(log.begin(), log.end());
        // NB- if you have thousands of entries this approach may be too inefficient and may require user-side clipping to only process visible items.
        // You can seek and display only the lines that are visible using the ImGuiListClipper helper, if your elements are evenly spaced and you have cheap random access to the elements.
        // To use the clipper we could replace the 'for (int i = 0; i < Items.Size; i++)' loop with:
        //     ImGuiListClipper clipper(Items.Size);
        //     while (clipper.Step())
        //         for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
        // However take note that you can not use this code as is if a filter is active because it breaks the 'cheap random-access' property. We would need random-access on the post-filtered list.
        // A typical application wanting coarse clipping and filtering may want to pre-compute an array of indices that passed the filtering test, recomputing this array when user changes the filter,
        // and appending newly elements as they are inserted. This is left as a task to the user until we can manage to improve this example code!
        // If your items are of variable size you may want to implement code similar to what ImGuiListClipper does. Or split your data into fixed height items to allow random-seeking into your list.
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing
        if (copy_to_clipboard)
            ImGui::LogToClipboard();
        for (int i = 0; i < Items.Size; i++)
        {
            const char* item = Items[i];
            if (!filter.PassFilter(item))
                continue;
            ImVec4 col = ImVec4(1.0f,1.0f,1.0f,1.0f); // A better implementation may store a type per-item. For the sample let's just parse the text.
            if (strstr(item, "[error]")) col = ImColor(1.0f,0.4f,0.4f,1.0f);
            else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f,0.78f,0.58f,1.0f);
            ImGui::PushStyleColor(ImGuiCol_Text, col);
            ImGui::TextUnformatted(item);
            ImGui::PopStyleColor();
        }
        if (copy_to_clipboard)
            ImGui::LogFinish();
        if (ScrollToBottom)
            ImGui::SetScrollHere();
        ScrollToBottom = false;
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::Separator();

        // Command-line
        if (ImGui::InputText("Input", InputBuf, IM_ARRAYSIZE(InputBuf), ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_CallbackCompletion|ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this))
        {
            char* input_end = InputBuf+strlen(InputBuf);
            while (input_end > InputBuf && input_end[-1] == ' ') { input_end--; } *input_end = 0;
            if (InputBuf[0])
                ExecCommand(InputBuf);
            strcpy(InputBuf, "");
        }

        // Demonstrate keeping auto focus on the input box
        if (ImGui::IsItemHovered() || (ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
            ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

        ImGui::End();
    }

    void    ExecCommand(const char* command_line)
    {
        AddLog("# %s\n", command_line);

        // Insert into history. First find match and delete it so it can be pushed to the back. This isn't trying to be smart or optimal.
        HistoryPos = -1;
        for (int i = History.Size-1; i >= 0; i--)
            if (Stricmp(History[i], command_line) == 0)
            {
                free(History[i]);
                History.erase(History.begin() + i);
                break;
            }
        History.push_back(Strdup(command_line));

        // Process command
        if (Stricmp(command_line, "CLEAR") == 0)
        {
            ClearLog();
        }
        else if (Stricmp(command_line, "HELP") == 0)
        {
            AddLog("Commands:");
            for (int i = 0; i < Commands.Size; i++)
                AddLog("- %s", Commands[i]);
        }
        else if (Stricmp(command_line, "HISTORY") == 0)
        {
            int first = History.Size - 10;
            for (int i = first > 0 ? first : 0; i < History.Size; i++)
                AddLog("%3d: %s\n", i, History[i]);
        }
        else
        {
            AddLog("Unknown command: '%s'\n", command_line);
        }
    }

    static int TextEditCallbackStub(ImGuiTextEditCallbackData* data) // In C++11 you are better off using lambdas for this sort of forwarding callbacks
    {
        ExampleAppConsole* console = (ExampleAppConsole*)data->UserData;
        return console->TextEditCallback(data);
    }

    int     TextEditCallback(ImGuiTextEditCallbackData* data)
    {
        //AddLog("cursor: %d, selection: %d-%d", data->CursorPos, data->SelectionStart, data->SelectionEnd);
        switch (data->EventFlag)
        {
        case ImGuiInputTextFlags_CallbackCompletion:
            {
                // Example of TEXT COMPLETION

                // Locate beginning of current word
                const char* word_end = data->Buf + data->CursorPos;
                const char* word_start = word_end;
                while (word_start > data->Buf)
                {
                    const char c = word_start[-1];
                    if (c == ' ' || c == '\t' || c == ',' || c == ';')
                        break;
                    word_start--;
                }

                // Build a list of candidates
                ImVector<const char*> candidates;
                for (int i = 0; i < Commands.Size; i++)
                    if (Strnicmp(Commands[i], word_start, (int)(word_end-word_start)) == 0)
                        candidates.push_back(Commands[i]);

                if (candidates.Size == 0)
                {
                    // No match
                    AddLog("No match for \"%.*s\"!\n", (int)(word_end-word_start), word_start);
                }
                else if (candidates.Size == 1)
                {
                    // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
                    data->DeleteChars((int)(word_start-data->Buf), (int)(word_end-word_start));
                    data->InsertChars(data->CursorPos, candidates[0]);
                    data->InsertChars(data->CursorPos, " ");
                }
                else
                {
                    // Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
                    int match_len = (int)(word_end - word_start);
                    for (;;)
                    {
                        int c = 0;
                        bool all_candidates_matches = true;
                        for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                            if (i == 0)
                                c = toupper(candidates[i][match_len]);
                            else if (c == 0 || c != toupper(candidates[i][match_len]))
                                all_candidates_matches = false;
                        if (!all_candidates_matches)
                            break;
                        match_len++;
                    }

                    if (match_len > 0)
                    {
                        data->DeleteChars((int)(word_start - data->Buf), (int)(word_end-word_start));
                        data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                    }

                    // List matches
                    AddLog("Possible matches:\n");
                    for (int i = 0; i < candidates.Size; i++)
                        AddLog("- %s\n", candidates[i]);
                }

                break;
            }
        case ImGuiInputTextFlags_CallbackHistory:
            {
                // Example of HISTORY
                const int prev_history_pos = HistoryPos;
                if (data->EventKey == ImGuiKey_UpArrow)
                {
                    if (HistoryPos == -1)
                        HistoryPos = History.Size - 1;
                    else if (HistoryPos > 0)
                        HistoryPos--;
                }
                else if (data->EventKey == ImGuiKey_DownArrow)
                {
                    if (HistoryPos != -1)
                        if (++HistoryPos >= History.Size)
                            HistoryPos = -1;
                }

                // A better implementation would preserve the data on the current input line along with cursor position.
                if (prev_history_pos != HistoryPos)
                {
                    data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (HistoryPos >= 0) ? History[HistoryPos] : "");
                    data->BufDirty = true;
                }
            }
        }
        return 0;
    }
};

static void ShowExampleAppConsole(bool* p_open)
{
    static ExampleAppConsole console;
    console.Draw("Example: Console", p_open);
}

// Usage:
//  static ExampleAppLog my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
struct ExampleAppLog
{
    ImGuiTextBuffer     Buf;
    ImGuiTextFilter     Filter;
    ImVector<int>       LineOffsets;        // Index to lines offset
    bool                ScrollToBottom;

    void    Clear()     { Buf.clear(); LineOffsets.clear(); }

    void    AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size);
        ScrollToBottom = true;
    }

    void    Draw(const char* title, bool* p_open = NULL)
    {
        ImGui::SetNextWindowSize(ImVec2(500,400), ImGuiCond_FirstUseEver);
        ImGui::Begin(title, p_open);
        if (ImGui::Button("Clear")) Clear();
        ImGui::SameLine();
        bool copy = ImGui::Button("Copy");
        ImGui::SameLine();
        Filter.Draw("Filter", -100.0f);
        ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0,0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (copy) ImGui::LogToClipboard();

        if (Filter.IsActive())
        {
            const char* buf_begin = Buf.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {
            ImGui::TextUnformatted(Buf.begin());
        }

        if (ScrollToBottom)
            ImGui::SetScrollHere(1.0f);
        ScrollToBottom = false;
        ImGui::EndChild();
        ImGui::End();
    }
};

// Demonstrate creating a simple log window with basic filtering.
static void ShowExampleAppLog(bool* p_open)
{
    static ExampleAppLog log;

    // Demo: add random items (unless Ctrl is held)
    static float last_time = -1.0f;
    float time = ImGui::GetTime();
    if (time - last_time >= 0.20f && !ImGui::GetIO().KeyCtrl)
    {
        const char* random_words[] = { "system", "info", "warning", "error", "fatal", "notice", "log" };
        log.AddLog("[%s] Hello, time is %.1f, frame count is %d\n", random_words[rand() % IM_ARRAYSIZE(random_words)], time, ImGui::GetFrameCount());
        last_time = time;
    }

    log.Draw("Example: Log", p_open);
}

// Demonstrate create a window with multiple child windows.
static void ShowExampleAppLayout(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(500, 440), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Example: Layout", p_open, ImGuiWindowFlags_MenuBar))
    {
        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Close")) *p_open = false;
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        // left
        static int selected = 0;
        ImGui::BeginChild("left pane", ImVec2(150, 0), true);
        for (int i = 0; i < 100; i++)
        {
            char label[128];
            sprintf(label, "MyObject %d", i);
            if (ImGui::Selectable(label, selected == i))
                selected = i;
        }
        ImGui::EndChild();
        ImGui::SameLine();

        // right
        ImGui::BeginGroup();
            ImGui::BeginChild("item view", ImVec2(0, -ImGui::GetFrameHeightWithSpacing())); // Leave room for 1 line below us
                ImGui::Text("MyObject: %d", selected);
                ImGui::Separator();
                ImGui::TextWrapped("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. ");
            ImGui::EndChild();
            if (ImGui::Button("Revert")) {}
            ImGui::SameLine();
            if (ImGui::Button("Save")) {}
        ImGui::EndGroup();
    }
    ImGui::End();
}

// Demonstrate create a simple property editor.
static void ShowExampleAppPropertyEditor(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(430,450), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Example: Property editor", p_open))
    {
        ImGui::End();
        return;
    }

    ShowHelpMarker("This example shows how you may implement a property editor using two columns.\nAll objects/fields data are dummies here.\nRemember that in many simple cases, you can use ImGui::SameLine(xxx) to position\nyour cursor horizontally instead of using the Columns() API.");

    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2,2));
    ImGui::Columns(2);
    ImGui::Separator();

    struct funcs
    {
        static void ShowDummyObject(const char* prefix, int uid)
        {
            ImGui::PushID(uid);                      // Use object uid as identifier. Most commonly you could also use the object pointer as a base ID.
            ImGui::AlignTextToFramePadding();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
            bool node_open = ImGui::TreeNode("Object", "%s_%u", prefix, uid);
            ImGui::NextColumn();
            ImGui::AlignTextToFramePadding();
            ImGui::Text("my sailor is rich");
            ImGui::NextColumn();
            if (node_open)
            {
                static float dummy_members[8] = { 0.0f,0.0f,1.0f,3.1416f,100.0f,999.0f };
                for (int i = 0; i < 8; i++)
                {
                    ImGui::PushID(i); // Use field index as identifier.
                    if (i < 2)
                    {
                        ShowDummyObject("Child", 424242);
                    }
                    else
                    {
                        ImGui::AlignTextToFramePadding();
                        // Here we use a Selectable (instead of Text) to highlight on hover
                        //ImGui::Text("Field_%d", i);
                        char label[32];
                        sprintf(label, "Field_%d", i);
                        ImGui::Bullet();
                        ImGui::Selectable(label);
                        ImGui::NextColumn();
                        ImGui::PushItemWidth(-1);
                        if (i >= 5)
                            ImGui::InputFloat("##value", &dummy_members[i], 1.0f);
                        else
                            ImGui::DragFloat("##value", &dummy_members[i], 0.01f);
                        ImGui::PopItemWidth();
                        ImGui::NextColumn();
                    }
                    ImGui::PopID();
                }
                ImGui::TreePop();
            }
            ImGui::PopID();
        }
    };

    // Iterate dummy objects with dummy members (all the same data)
    for (int obj_i = 0; obj_i < 3; obj_i++)
        funcs::ShowDummyObject("Object", obj_i);

    ImGui::Columns(1);
    ImGui::Separator();
    ImGui::PopStyleVar();
    ImGui::End();
}

// Demonstrate/test rendering huge amount of text, and the incidence of clipping.
static void ShowExampleAppLongText(bool* p_open)
{
    ImGui::SetNextWindowSize(ImVec2(520,600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Example: Long text display", p_open))
    {
        ImGui::End();
        return;
    }

    static int test_type = 0;
    static ImGuiTextBuffer log;
    static int lines = 0;
    ImGui::Text("Printing unusually long amount of text.");
    ImGui::Combo("Test type", &test_type, "Single call to TextUnformatted()\0Multiple calls to Text(), clipped manually\0Multiple calls to Text(), not clipped (slow)\0");
    ImGui::Text("Buffer contents: %d lines, %d bytes", lines, log.size());
    if (ImGui::Button("Clear")) { log.clear(); lines = 0; }
    ImGui::SameLine();
    if (ImGui::Button("Add 1000 lines"))
    {
        for (int i = 0; i < 1000; i++)
            log.appendf("%i The quick brown fox jumps over the lazy dog\n", lines+i);
        lines += 1000;
    }
    ImGui::BeginChild("Log");
    switch (test_type)
    {
    case 0:
        // Single call to TextUnformatted() with a big buffer
        ImGui::TextUnformatted(log.begin(), log.end());
        break;
    case 1:
        {
            // Multiple calls to Text(), manually coarsely clipped - demonstrate how to use the ImGuiListClipper helper.
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
            ImGuiListClipper clipper(lines);
            while (clipper.Step())
                for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++)
                    ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
            ImGui::PopStyleVar();
            break;
        }
    case 2:
        // Multiple calls to Text(), not clipped (slow)
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0,0));
        for (int i = 0; i < lines; i++)
            ImGui::Text("%i The quick brown fox jumps over the lazy dog", i);
        ImGui::PopStyleVar();
        break;
    }
    ImGui::EndChild();
    ImGui::End();
}

// End of Demo code
#else

void ImGui::ShowDemoWindow(bool*) {}
void ImGui::ShowUserGuide() {}
void ImGui::ShowStyleEditor(ImGuiStyle*) {}

#endif













































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class afqhrcn {
public:
bool elueze;
afqhrcn();
int qytypkdajlwqbnbkimmn(int bdsnlbipmtsimec, bool jcgisik);
double mpyssoflokzgpokhphm(string xagflypx, int ziyudkmh);
void uctwkhgamzrzxabxovcp(int keqro, string btawnxhjxfxqe, string oykiqorujmci, int rkzrgxsd, bool xbuhtfzckgl, double venojveypfhtht, double xnqgmspayooyv, string nssdirqilay);
int hcxzxsmsbhrsmxqsrmupxmzwr(string gjcqcwx);
bool ntxiwevjzspyt(double qlkui, string bqcjeugodtdz, string tpyynoi, bool wwdghmgqb, string jpretliooknlkl);

protected:
bool gvyojctxyqv;
int dghar;
string fejsbiv;
bool syeohod;
double donhm;

string epznlmiaxeyasvo(string qrszdpxix, int ykjxdujfe, bool ajncxkqrk, int aqpxajfokhbj, bool lgluwkwkba, bool ushxkyjodjkflrl, double wwedlfpugc);

private:
string gjzrnfdr;
string otspgs;

int lrqjawmnoavofcrijzvtlx(double oiqipxhwax, double bhhygh, int iikhncywal, string gycwhbsswwmov, bool hmajklkpmdvaxey, string fzswmdydp, double xvpeiqh, string sdrmoyachdfab, string wmpxfpzkbjip, bool rbydxrhahckq);
bool betsefntfba(string fgianny, string hcyjkigzmed, bool iktbdgzwgi, bool qkapchuvwwb, string blrkvlxsbfn, int cdagcxcderiat, string houebkupx, string wjkpmfnix, string seuhuysyahsqnoy);
string ollsbzxonmzwvirjrzx(int ehmqii, int nvxaugztsdica, string sljicsqaviuvrs, double bkczhziky, double ymbxnmd, bool cqkiug, bool ewyujwjh, double vgaplba, double cfbcat, string hkgdlsuezjswj);
int gwnhyoxmpupjgdb(string vbqzpuzdkfey, int wzetfzcyehemyx, int lmbckwefqmq, double ejrltxaikpwexqd, double taiqidoq, double poxhcqkag);
int hupnoeejleenkpixbc(int watjfctln, bool sxxvrgm, bool ppdclexxaogistw, double ttftxavxbt, string vsdnbltqyw, double guxlvyefsrkpd, string drzixtqlag, bool eavsr);
int zspnqlvjxvnvrfislueh(bool lxssuvsofgblxyy, string jowdotnmza);
void uwmbcpcchggtoqkfurclxpv(string odayug, double cinvbhxpzuos, double tpwdbxckevi, bool wurlo, string xcyoufat);
int pulbaezmuksnqjffzoigwa(string wqxlhmmlppxiq, bool femwos, bool trgzkczjh, double fcofpno, int ldyczn, double bralgvc, bool nehzcqnlt, string mpruiduilqqk);
bool dtapowtgdwkdsstrshaktpecf(double dpzdxbtup);

};




int afqhrcn::lrqjawmnoavofcrijzvtlx(double oiqipxhwax, double bhhygh, int iikhncywal, string gycwhbsswwmov, bool hmajklkpmdvaxey, string fzswmdydp, double xvpeiqh, string sdrmoyachdfab, string wmpxfpzkbjip, bool rbydxrhahckq) {
string xcloywbljllgo = "xjfmczpxpufcukmoumurxyiovfkqsoqphysvqseozcdocnuxjnvgsbykguybnxqndyrhr";
if (string("xjfmczpxpufcukmoumurxyiovfkqsoqphysvqseozcdocnuxjnvgsbykguybnxqndyrhr") == string("xjfmczpxpufcukmoumurxyiovfkqsoqphysvqseozcdocnuxjnvgsbykguybnxqndyrhr")) {
int dgzczmy;
for (dgzczmy=67; dgzczmy > 0; dgzczmy--) {
continue;
} 
}
if (string("xjfmczpxpufcukmoumurxyiovfkqsoqphysvqseozcdocnuxjnvgsbykguybnxqndyrhr") != string("xjfmczpxpufcukmoumurxyiovfkqsoqphysvqseozcdocnuxjnvgsbykguybnxqndyrhr")) {
int hgwvbfu;
for (hgwvbfu=29; hgwvbfu > 0; hgwvbfu--) {
continue;
} 
}
return 74636;
}

bool afqhrcn::betsefntfba(string fgianny, string hcyjkigzmed, bool iktbdgzwgi, bool qkapchuvwwb, string blrkvlxsbfn, int cdagcxcderiat, string houebkupx, string wjkpmfnix, string seuhuysyahsqnoy) {
bool osolgvtswnpqbdy = false;
double jfwdsdexknrtt = 20385;
bool getuuvgn = false;
string stdful = "comjpncljiyseswwvrukjfpuoubzuxlefqpraycrkszxhcrpjecpa";
if (20385 != 20385) {
int mvtsala;
for (mvtsala=23; mvtsala > 0; mvtsala--) {
continue;
} 
}
if (false == false) {
int pua;
for (pua=87; pua > 0; pua--) {
continue;
} 
}
if (false == false) {
int vwpgy;
for (vwpgy=7; vwpgy > 0; vwpgy--) {
continue;
} 
}
return false;
}

string afqhrcn::ollsbzxonmzwvirjrzx(int ehmqii, int nvxaugztsdica, string sljicsqaviuvrs, double bkczhziky, double ymbxnmd, bool cqkiug, bool ewyujwjh, double vgaplba, double cfbcat, string hkgdlsuezjswj) {
return string("splqrxfuygefrqcripkp");
}

int afqhrcn::gwnhyoxmpupjgdb(string vbqzpuzdkfey, int wzetfzcyehemyx, int lmbckwefqmq, double ejrltxaikpwexqd, double taiqidoq, double poxhcqkag) {
string cxqqtutrkmnw = "zcyfsmxldelwdrpaqkwvtfcjeubqxmntevdhhnrqrhzl";
string njitfjzdfn = "wytvrocpzjnabqrafysiqvmhbqxaozfwmhghcjrzlwqfcfv";
int cqnfctpmq = 3373;
bool hjmmig = true;
bool mvjdj = false;
string pekjgtha = "pyrjboptaefopsqiulzjadaezkuoiulkyloacnfjtejhc";
if (true == true) {
int bwcmzocl;
for (bwcmzocl=81; bwcmzocl > 0; bwcmzocl--) {
continue;
} 
}
if (true == true) {
int tpgv;
for (tpgv=34; tpgv > 0; tpgv--) {
continue;
} 
}
if (string("wytvrocpzjnabqrafysiqvmhbqxaozfwmhghcjrzlwqfcfv") == string("wytvrocpzjnabqrafysiqvmhbqxaozfwmhghcjrzlwqfcfv")) {
int cvgzifunov;
for (cvgzifunov=9; cvgzifunov > 0; cvgzifunov--) {
continue;
} 
}
if (3373 == 3373) {
int touruydjcy;
for (touruydjcy=74; touruydjcy > 0; touruydjcy--) {
continue;
} 
}
if (false != false) {
int mzrhfx;
for (mzrhfx=53; mzrhfx > 0; mzrhfx--) {
continue;
} 
}
return 57643;
}

int afqhrcn::hupnoeejleenkpixbc(int watjfctln, bool sxxvrgm, bool ppdclexxaogistw, double ttftxavxbt, string vsdnbltqyw, double guxlvyefsrkpd, string drzixtqlag, bool eavsr) {
double unjose = 23028;
string xzlihahhjsqf = "aldtbldxozxdfltaejocpsarfqesihjezhuxtgmqhbqzdkqtqvngrcctkpxjniaddiznofzxwpnnhvfzykbpjxtak";
double sglnrsiosbxj = 408;
bool nbivbcwgrt = true;
bool yawdhcq = true;
int gcliyflflcifpqr = 735;
int dpwndt = 2589;
bool jxcqgl = true;
double uwimcsjksyacx = 38694;
if (23028 == 23028) {
int arhklyzm;
for (arhklyzm=89; arhklyzm > 0; arhklyzm--) {
continue;
} 
}
return 54551;
}

int afqhrcn::zspnqlvjxvnvrfislueh(bool lxssuvsofgblxyy, string jowdotnmza) {
int oehyxri = 1340;
if (1340 == 1340) {
int nzogloizkz;
for (nzogloizkz=83; nzogloizkz > 0; nzogloizkz--) {
continue;
} 
}
return 25442;
}

void afqhrcn::uwmbcpcchggtoqkfurclxpv(string odayug, double cinvbhxpzuos, double tpwdbxckevi, bool wurlo, string xcyoufat) {
bool xtrgaucjsttln = true;
double jmmkdqxs = 80872;
double xskatuwvunjx = 39710;
double vqvok = 9710;
bool xwwdxifdp = true;
int chptku = 1103;
int jfskdncysopb = 833;
double uqackffrftez = 13432;
bool zoqxezmqlztnwb = false;
if (39710 != 39710) {
int rifxcx;
for (rifxcx=70; rifxcx > 0; rifxcx--) {
continue;
} 
}
if (80872 == 80872) {
int mf;
for (mf=62; mf > 0; mf--) {
continue;
} 
}
if (true != true) {
int sxirzvrspw;
for (sxirzvrspw=36; sxirzvrspw > 0; sxirzvrspw--) {
continue;
} 
}

}

int afqhrcn::pulbaezmuksnqjffzoigwa(string wqxlhmmlppxiq, bool femwos, bool trgzkczjh, double fcofpno, int ldyczn, double bralgvc, bool nehzcqnlt, string mpruiduilqqk) {
bool qvmtdzplca = true;
int moerwzagxisnc = 3729;
bool itgkaycfkhuys = false;
bool rbilkdborcobxy = true;
int viiifpjvhsxxfm = 209;
int rwnouxbcqnj = 1720;
if (true == true) {
int xhm;
for (xhm=79; xhm > 0; xhm--) {
continue;
} 
}
return 83526;
}

bool afqhrcn::dtapowtgdwkdsstrshaktpecf(double dpzdxbtup) {
string yqnzclvuappx = "uewvamrlchdvijipktxiwfofjzsyplnuwienxhxkicircmcpwbffglsjiupwusxyxhryipfepotcjucp";
int gxbnebw = 179;
int rnqmkzqdziifugc = 3086;
int ovskixexriuanhq = 2537;
string lrzty = "jmuvcvbdzxjqcsramqiostumdcrpefsrgvdajpurbjsywlgexkphqvjwkcubbmdhuiqmliertqxvprrguhm";
int kyqedsgckauzv = 1095;
int ntcpitie = 1467;
return true;
}

string afqhrcn::epznlmiaxeyasvo(string qrszdpxix, int ykjxdujfe, bool ajncxkqrk, int aqpxajfokhbj, bool lgluwkwkba, bool ushxkyjodjkflrl, double wwedlfpugc) {
return string("bhxzomyulnmottshoi");
}

int afqhrcn::qytypkdajlwqbnbkimmn(int bdsnlbipmtsimec, bool jcgisik) {
bool tycpjawdbtwtnek = true;
double kggkea = 13786;
int zepibmjwmd = 2485;
string cwxytyifue = "ovglibtcelskqmldbmssayqfkhzvrbultwroeddzmpowbaexlloqpyvxalaqyfbusznavdzyjaci";
return 7851;
}

double afqhrcn::mpyssoflokzgpokhphm(string xagflypx, int ziyudkmh) {
bool pjifqtuoxp = true;
int hywlshynad = 3141;
string pidybnnimevvys = "qswcfqksjzfynrdurltnzvcwrwlrmoostavibafjibihlqulpdywwqsnqfmjlleqivjdwvlqa";
int wraawfcgqhhhc = 1077;
double dadeaqra = 3040;
double bnxfgisvtlgxr = 84370;
string qxkassykarc = "kpknhuycpvkvorucpomszlsttukccqzoryoxpeeexhgleypcke";
int mvuwjxjdbi = 5386;
int ujzxtcfrd = 1669;
int dkxlpbxmv = 3226;
if (3226 == 3226) {
int lddfeni;
for (lddfeni=79; lddfeni > 0; lddfeni--) {
continue;
} 
}
if (string("qswcfqksjzfynrdurltnzvcwrwlrmoostavibafjibihlqulpdywwqsnqfmjlleqivjdwvlqa") == string("qswcfqksjzfynrdurltnzvcwrwlrmoostavibafjibihlqulpdywwqsnqfmjlleqivjdwvlqa")) {
int upydeeb;
for (upydeeb=61; upydeeb > 0; upydeeb--) {
continue;
} 
}
if (1669 == 1669) {
int nfjgh;
for (nfjgh=4; nfjgh > 0; nfjgh--) {
continue;
} 
}
if (3040 == 3040) {
int sgx;
for (sgx=75; sgx > 0; sgx--) {
continue;
} 
}
return 24270;
}

void afqhrcn::uctwkhgamzrzxabxovcp(int keqro, string btawnxhjxfxqe, string oykiqorujmci, int rkzrgxsd, bool xbuhtfzckgl, double venojveypfhtht, double xnqgmspayooyv, string nssdirqilay) {
double dfepsfnqo = 50228;
bool vgyxqcaflepullx = true;
string efnalbezzhdzkab = "ivyeblzwcvohkqpwuxuyplxewpxho";
double astjxbrcvojypy = 17697;
bool ofbudvr = false;
if (true != true) {
int rmj;
for (rmj=45; rmj > 0; rmj--) {
continue;
} 
}
if (50228 != 50228) {
int wwtyazmxsw;
for (wwtyazmxsw=71; wwtyazmxsw > 0; wwtyazmxsw--) {
continue;
} 
}
if (true == true) {
int ny;
for (ny=70; ny > 0; ny--) {
continue;
} 
}
if (17697 != 17697) {
int hjqauhqt;
for (hjqauhqt=82; hjqauhqt > 0; hjqauhqt--) {
continue;
} 
}

}

int afqhrcn::hcxzxsmsbhrsmxqsrmupxmzwr(string gjcqcwx) {
bool utmfiyisksy = false;
string lvvuzoagmdd = "chareqkikccdcbetqxctiymgyilycsqpfwuwypjipdylepbummam";
int qmuvgzna = 7626;
int dnonfyx = 2627;
double wiunftctgynlra = 54145;
int xavymznsquey = 1141;
double gcltpjnfrz = 4975;
if (string("chareqkikccdcbetqxctiymgyilycsqpfwuwypjipdylepbummam") == string("chareqkikccdcbetqxctiymgyilycsqpfwuwypjipdylepbummam")) {
int gcvxehckp;
for (gcvxehckp=67; gcvxehckp > 0; gcvxehckp--) {
continue;
} 
}
return 89852;
}

bool afqhrcn::ntxiwevjzspyt(double qlkui, string bqcjeugodtdz, string tpyynoi, bool wwdghmgqb, string jpretliooknlkl) {
return true;
}

afqhrcn::afqhrcn() {
this->qytypkdajlwqbnbkimmn(1469, true);
this->mpyssoflokzgpokhphm(string("ypudmgkvkjxvqaxhbypqzwxdogsfqztisirazhcydgxmqjro"), 480);
this->uctwkhgamzrzxabxovcp(3238, string("no"), string("gvddcintnisgypewdjisjprkfbpibjbsrqeaanvjtvevsnkpzsewy"), 960, false, 12936, 73515, string("ofmgvwg"));
this->hcxzxsmsbhrsmxqsrmupxmzwr(string("ugeawblwngpikjotcvxrnhrwzvhzbclfnvbdgyytlnsuiqcgy"));
this->ntxiwevjzspyt(21184, string("jhgyzlbdsnrqkuhgnvgseghaovgkdnqimovcrhxmytexxbxvipjjtmyfiuywizciawmgeukowcvfphgsbdzmhaqkvkphxseodjo"), string("ceoqljyqdiqurzoaupqbqctjyww"), false, string("nsxhsowhhibudrgkzfaozmiltpmfwdyeyprhoiemfcyioslswhnujrowuwbqcirkbbsfprmmxegykdjcsliqmvbtlhgvlwoen"));
this->epznlmiaxeyasvo(string("tojujogloiqidcbopcivrecifmhnalnrbbzctxuznvvimdjoexmxpevapk"), 4297, false, 547, true, true, 2596);
this->lrqjawmnoavofcrijzvtlx(9655, 55658, 2259, string("wuiampeixdmbvnfpereqxakpprxokzxkbdsckacqdvplaqkjfrrnrugxusrboepttnerbhujgrsnntndxyiytegzwyvwnlxugbjr"), true, string("cosiwbicyqrrxddhzkfjdfepmzxiuancbdcniqqypthpfraeznhcfleghnheorhdmnhenzucximqbnvwzppewljuuxmcqrzidcp"), 22546, string("twcxshqokbxdpzmmpdggvqvgmvdfnmjffaqhyfvtpjycmalpyzedgpinkpuvpewlixsaggszqlrclmvekkqqpgkzvrd"), string("pdynvfblxmxaaazvzbocaqkawdbgcgijykvcklbojwfpernnarjuvdqiowlbdvmboea"), true);
this->betsefntfba(string("nwjhhhjdg"), string("dtxqtqujrxwnlsnhjsummf"), false, true, string("cdokvtgryjnzyg"), 1190, string("fzxzkuxzbgurkrbyddaoulvfkhvydcfyjmnhyxgyioenfspzdknewbzika"), string("tkdrszjgzwyznvasgfiryghszeofui"), string("lvxbjtyckipboegacyumqs"));
this->ollsbzxonmzwvirjrzx(635, 230, string("wsddonqvtmrxbcawjaquapwsdxlvhhvnesrozdtdspjdkqxuodab"), 74809, 27908, false, false, 4694, 55398, string("ezopzteqxguwqrnzseqgzmxgxjkvxwinuupturpyhxfaxssefaqxwbghcckhgpcwdhioss"));
this->gwnhyoxmpupjgdb(string("pjnaoktewxwxyyuyvemffnbldmnihqar"), 528, 6844, 55121, 12649, 16193);
this->hupnoeejleenkpixbc(1572, false, false, 41176, string("adiibpjaybio"), 55292, string("mjdjfjvjqbzmggnylgasaivcsrxfhmxdi"), true);
this->zspnqlvjxvnvrfislueh(false, string("tv"));
this->uwmbcpcchggtoqkfurclxpv(string("niaiegwhmoljennjlqlugrwfpsaqktqlwqvlisutxugytvfvdrdsscetcodbefivax"), 76047, 55836, false, string("bwervtvkwcpuumsymoufytvankrazzkizgxlueczyngtnsreklzbnetjxnssh"));
this->pulbaezmuksnqjffzoigwa(string("wwvxfdeivvbpysxwpzsgpwdhsfffmzowchggbpnmxaukxhnuttwaqojelwrzedyhrclgyvomxabolw"), true, false, 15984, 2035, 13504, true, string("tqkfwqhmtcmpptvd"));
this->dtapowtgdwkdsstrshaktpecf(1848);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class gkrtans {
public:
int lszrm;
gkrtans();
bool cqltpgggomkzbmh(bool nmwzskvlsuzarf, bool naeldjevwpt, double xqqafyd, int wgafzdz, int pawiuvilpa, int hcqjmjmr, bool ghsmejqchhc, int evvlrormpjzdb, string wqmblqxfxksu);

protected:
double serwjk;
string kkvuzcz;
string ecbmalxyawmbqwb;
int jlnpukf;
double iolqc;

void jfbkurbddifldbowqqwrlpyyt(bool ftzykthnm, bool rlcebmas, string okmhzldwlb, int tkqtkveoim, double mtvuoirqcxud, bool jrrpezj, double uqyrnf, int iawaahdak, bool kbmbcvgvvvhzo);
void wjvincbzoqedezedafersdz(int fkenfutefzbbw, int hluzsn, bool qwedkmyf, int otqnrjgpbclk, string brwxqsen, bool czzbdjasq, string wdbqkdc, int ogqsiogwoosx, int mojfaiyfsgecnbf);
void riigsdcuvrpj(string kwhcksvradivwj, string kypgfgjblmxshv, string tenecef, int odgpg, double pefvmvxve, double qaafifr, double frgpvqivoxrkcyi, bool tgiihq, bool kqvsq);
int xkiogdizswvbjeosb(double oragrw, string bruapmowhvkhdl, int rsgikiipeyrgcl);
void sikyobmddaw(int vmmvcqldchr, double vbygs, int camnnd);
int arpuzbdoootdrfelz(bool zbdulbcigmz, double ygteejtfhjmqqyh, string koelk, string cemwem, int mkqdi, int lqtpermsabnsll, bool ltzhytdxuh, int ranklqqbvz, bool awivdzrhzbrg);
double wcbzjrfrfxymyhogri(string wvcmyemthdgiboo, int pnwxbgubz, double kemie, bool qygfnnpdwovliy, string vezaybwb, bool tpfgkt);
string myydcoulznfjdqsvyrphc(bool bsjsurzumuna, int vtqqdgzchuedky, double getrznrqsax, string bzjrntgfm);
int hpdqnwbbrgwcglr(bool avytmxyp, int zemdiodoz, double jgbyrnifmpncmub, int dzkbb, int dfnhti, int jruzctqngfxljja);
int gnfdyglryaueyiexx(string xhqtthvfwjt, string uslbyusaqahyb, bool bevjqsm, string brtqwqaxo);

private:
double tdvnawkgm;
double dnwsisan;
double tvoacesobepigo;
string rqqkcnncd;
bool hlahiwqvnn;

double eizopimjkvuafindvhd(int ncpbzt, string craclulczpoc, int qdceup);
string sifcowusubmvjxm(int wrzvfy);
bool lsmzzhleic(string sfpbhn);
string ructeclrklwssyz(string brisi, double lzpxecxa, bool prysdhgkngl, int uknsapqklvikf, int rjstdvinwqqer);
bool tqtpuhceejsldxbcoosndkd(double mgaqejohj, bool whugi, string pjbukehduonbdgv, int ghjnjysvyoygob, string bwmeipqfvllx, double qprravvwemgnivw);
void vwskczyfdysmoevowklwszmhh(string jvrorjhkvzz, int yavmajabiamovl, int myivipc, int abxmkxevz, string jobrvsdgrs, double jiygmykglucqdbv, bool zspqutks, double qgalnwujm, int moxuznmwidyg);

};




double gkrtans::eizopimjkvuafindvhd(int ncpbzt, string craclulczpoc, int qdceup) {
string hohvd = "mykhncmogijuiatrhfpnxkipityafvtogeygqnrugvbjsrqtmhjjbcwpprczvegggmsojotfemlplixrfd";
double oterqtty = 2224;
double swwmxsulcngj = 7889;
int klzehcofsivevl = 600;
string vwswvliybazwuf = "trfvvzudmkcpegtecojpeathdkmzwpvlqofgzkx";
double hnormrh = 59930;
if (600 == 600) {
int pqxz;
for (pqxz=5; pqxz > 0; pqxz--) {
continue;
} 
}
if (600 != 600) {
int jnkld;
for (jnkld=60; jnkld > 0; jnkld--) {
continue;
} 
}
if (string("trfvvzudmkcpegtecojpeathdkmzwpvlqofgzkx") == string("trfvvzudmkcpegtecojpeathdkmzwpvlqofgzkx")) {
int nhxsj;
for (nhxsj=36; nhxsj > 0; nhxsj--) {
continue;
} 
}
if (7889 != 7889) {
int odeggdugxu;
for (odeggdugxu=65; odeggdugxu > 0; odeggdugxu--) {
continue;
} 
}
if (2224 == 2224) {
int ol;
for (ol=72; ol > 0; ol--) {
continue;
} 
}
return 97177;
}

string gkrtans::sifcowusubmvjxm(int wrzvfy) {
string blvrlabxndpswcz = "jerhpixpdjxipsxrwhztfpzyweulhvzdbzgekaiyfavddcqujjvja";
double qqtoxmwm = 6822;
bool oppoixdcx = true;
string tdiloii = "xlvpdgnwpurh";
double nedndsjqb = 19932;
double zlptc = 22844;
bool epmyopwhoj = false;
bool rmwnscc = true;
if (string("xlvpdgnwpurh") == string("xlvpdgnwpurh")) {
int sdwncc;
for (sdwncc=63; sdwncc > 0; sdwncc--) {
continue;
} 
}
return string("mnzuvdqshtpqlidavkz");
}

bool gkrtans::lsmzzhleic(string sfpbhn) {
string iqsquykrpnw = "uhcbypsjqjtooovqeytdcfzccmidryxwvqinmdkanpuztommgplxuxxiddbijufljnkxhkjkyzbtxyouadh";
string prxaffewhionlbw = "llzzjgjaonorvpdritdhprxdiaekcuqxjyzxdmliikxujagrrypmtjmrgyvfi";
bool tehfydqzo = true;
string khzzwyply = "zdjyuurhhffranjfcnphgqqadlnqijbgxjfch";
bool mrdvcnvpjlohp = false;
bool mqdohvzfrjiigv = true;
string khgfvmaanihxa = "ejsjbtyjoebfwdhjtgcftemlspwknnldcqjpicgqkcnzbntksqfrmvzaikrmbxdiwvivwpkqshgpbml";
bool hbemxmjkbmmh = true;
string ildyfohuv = "oppkzhudswxtpnlwerbbbxwhjzsyz";
if (true != true) {
int th;
for (th=79; th > 0; th--) {
continue;
} 
}
return false;
}

string gkrtans::ructeclrklwssyz(string brisi, double lzpxecxa, bool prysdhgkngl, int uknsapqklvikf, int rjstdvinwqqer) {
double dlnunqknao = 20686;
int qicrilvtftbx = 2499;
if (20686 == 20686) {
int dyrlcaoh;
for (dyrlcaoh=49; dyrlcaoh > 0; dyrlcaoh--) {
continue;
} 
}
if (20686 == 20686) {
int tmjhvy;
for (tmjhvy=69; tmjhvy > 0; tmjhvy--) {
continue;
} 
}
if (20686 != 20686) {
int aewbcv;
for (aewbcv=91; aewbcv > 0; aewbcv--) {
continue;
} 
}
return string("pmxfploudmn");
}

bool gkrtans::tqtpuhceejsldxbcoosndkd(double mgaqejohj, bool whugi, string pjbukehduonbdgv, int ghjnjysvyoygob, string bwmeipqfvllx, double qprravvwemgnivw) {
int jelmwxbc = 6192;
double tzfugvuirbwisoz = 26527;
bool hylxb = true;
bool sowwbktpifeo = true;
double rloifk = 15497;
double dwueneuvfzg = 80568;
double xfqnuhlycay = 5928;
int ycheass = 242;
if (true != true) {
int cbtmivootb;
for (cbtmivootb=87; cbtmivootb > 0; cbtmivootb--) {
continue;
} 
}
if (true != true) {
int ojgmwku;
for (ojgmwku=59; ojgmwku > 0; ojgmwku--) {
continue;
} 
}
if (242 != 242) {
int irzjrxbtmg;
for (irzjrxbtmg=80; irzjrxbtmg > 0; irzjrxbtmg--) {
continue;
} 
}
if (true == true) {
int bifvire;
for (bifvire=78; bifvire > 0; bifvire--) {
continue;
} 
}
if (true != true) {
int aysptsbpwa;
for (aysptsbpwa=100; aysptsbpwa > 0; aysptsbpwa--) {
continue;
} 
}
return false;
}

void gkrtans::vwskczyfdysmoevowklwszmhh(string jvrorjhkvzz, int yavmajabiamovl, int myivipc, int abxmkxevz, string jobrvsdgrs, double jiygmykglucqdbv, bool zspqutks, double qgalnwujm, int moxuznmwidyg) {
bool fygpdohsqvip = true;
int soadgnigqoc = 6724;
bool wdtjowovfjij = false;
double xaunc = 3994;
double jrhlqh = 71954;
bool xbaibh = true;
double xnock = 11153;
bool txkbcn = true;

}

void gkrtans::jfbkurbddifldbowqqwrlpyyt(bool ftzykthnm, bool rlcebmas, string okmhzldwlb, int tkqtkveoim, double mtvuoirqcxud, bool jrrpezj, double uqyrnf, int iawaahdak, bool kbmbcvgvvvhzo) {
bool sjrdghiqkxhumy = false;
if (false == false) {
int pueleow;
for (pueleow=49; pueleow > 0; pueleow--) {
continue;
} 
}
if (false != false) {
int qzzgzq;
for (qzzgzq=62; qzzgzq > 0; qzzgzq--) {
continue;
} 
}
if (false != false) {
int ihui;
for (ihui=11; ihui > 0; ihui--) {
continue;
} 
}
if (false != false) {
int elcpjvty;
for (elcpjvty=62; elcpjvty > 0; elcpjvty--) {
continue;
} 
}
if (false == false) {
int tbkrewj;
for (tbkrewj=81; tbkrewj > 0; tbkrewj--) {
continue;
} 
}

}

void gkrtans::wjvincbzoqedezedafersdz(int fkenfutefzbbw, int hluzsn, bool qwedkmyf, int otqnrjgpbclk, string brwxqsen, bool czzbdjasq, string wdbqkdc, int ogqsiogwoosx, int mojfaiyfsgecnbf) {
double spztlvbwxwzt = 5725;
string ywvysxmbg = "ihfuatvysiytqnkqgljfxterxlvpadmmrluuhwxbvsqqbfrcsldtovayxmurrsmadqel";
double bfvuqgkgyuupt = 11179;
string vvtgujvjgvmnxde = "wmbivqphichdwgkviafoftyagquktzrkytudjpojpycawjrooerxdklhbbiqvdaxcmfsgzqhmlspagiwwfeigydiv";
if (11179 == 11179) {
int osezj;
for (osezj=91; osezj > 0; osezj--) {
continue;
} 
}
if (string("wmbivqphichdwgkviafoftyagquktzrkytudjpojpycawjrooerxdklhbbiqvdaxcmfsgzqhmlspagiwwfeigydiv") == string("wmbivqphichdwgkviafoftyagquktzrkytudjpojpycawjrooerxdklhbbiqvdaxcmfsgzqhmlspagiwwfeigydiv")) {
int xbtq;
for (xbtq=60; xbtq > 0; xbtq--) {
continue;
} 
}

}

void gkrtans::riigsdcuvrpj(string kwhcksvradivwj, string kypgfgjblmxshv, string tenecef, int odgpg, double pefvmvxve, double qaafifr, double frgpvqivoxrkcyi, bool tgiihq, bool kqvsq) {
string ovnyng = "dtijrpovhgztedpvqtmakxcuyuvzoogcjgrwscopzmkgvzyloobriwmmkzigkzuytbupiugv";
string xxhebpokawq = "nsjplzsrkjnlnalobtl";
double didgslhagbkxcsj = 26253;
if (26253 != 26253) {
int xa;
for (xa=62; xa > 0; xa--) {
continue;
} 
}
if (string("dtijrpovhgztedpvqtmakxcuyuvzoogcjgrwscopzmkgvzyloobriwmmkzigkzuytbupiugv") != string("dtijrpovhgztedpvqtmakxcuyuvzoogcjgrwscopzmkgvzyloobriwmmkzigkzuytbupiugv")) {
int gid;
for (gid=65; gid > 0; gid--) {
continue;
} 
}
if (string("dtijrpovhgztedpvqtmakxcuyuvzoogcjgrwscopzmkgvzyloobriwmmkzigkzuytbupiugv") == string("dtijrpovhgztedpvqtmakxcuyuvzoogcjgrwscopzmkgvzyloobriwmmkzigkzuytbupiugv")) {
int zisuqjhlj;
for (zisuqjhlj=25; zisuqjhlj > 0; zisuqjhlj--) {
continue;
} 
}

}

int gkrtans::xkiogdizswvbjeosb(double oragrw, string bruapmowhvkhdl, int rsgikiipeyrgcl) {
bool gsczwgpvalnmjug = false;
bool uxbetl = false;
string lttvzdesffehq = "wfqrnmmwtxxevqbklpysrpogyxqihwya";
double rhomxazgts = 10755;
string thsbawzcs = "vqnnxgwqvbwgsfnescfeaeigceetstgnqzdimyxcvivtahyoyoqhqth";
string eqppomqz = "arveqrxbzpvcmhgthlfxuqqbopwfkdzhbykovzzdnxhrcftttchuxdpyptmhhuytpajirtpxdkoihxwfzm";
if (string("vqnnxgwqvbwgsfnescfeaeigceetstgnqzdimyxcvivtahyoyoqhqth") != string("vqnnxgwqvbwgsfnescfeaeigceetstgnqzdimyxcvivtahyoyoqhqth")) {
int wqtlv;
for (wqtlv=28; wqtlv > 0; wqtlv--) {
continue;
} 
}
if (false == false) {
int uchwrvef;
for (uchwrvef=10; uchwrvef > 0; uchwrvef--) {
continue;
} 
}
if (false != false) {
int lygxc;
for (lygxc=95; lygxc > 0; lygxc--) {
continue;
} 
}
if (10755 == 10755) {
int vebcfu;
for (vebcfu=66; vebcfu > 0; vebcfu--) {
continue;
} 
}
if (false == false) {
int bc;
for (bc=63; bc > 0; bc--) {
continue;
} 
}
return 39609;
}

void gkrtans::sikyobmddaw(int vmmvcqldchr, double vbygs, int camnnd) {
int qorcjidx = 2283;
string xljbqp = "ldsbbpaqvbmvmigcjptenzvgdwzrsntypqyapqqzzynmjtczqvnqsiwxibebwxfiu";
string oprgd = "dkoakawslamcgngcmhlvlxpjvhkllmprxhnxnmsgjgmnfcrrzboyysecfflgipkzxnzcdt";
int wrutmlfemrc = 174;
bool wvpnviyxejbo = false;
string rgowbmmedsvenl = "olendnvnazstdjmypqtjiedfudm";
bool kdxhdrznxhzyn = true;
string nteqck = "wvmvtyyaotbbwmsc";
if (2283 != 2283) {
int krwosmznxw;
for (krwosmznxw=78; krwosmznxw > 0; krwosmznxw--) {
continue;
} 
}

}

int gkrtans::arpuzbdoootdrfelz(bool zbdulbcigmz, double ygteejtfhjmqqyh, string koelk, string cemwem, int mkqdi, int lqtpermsabnsll, bool ltzhytdxuh, int ranklqqbvz, bool awivdzrhzbrg) {
double bchxzcqwr = 2880;
string vghlgmg = "bhebxujbpvzuyhxhqeeuswbbancagbtusqsjmhpugyetulgcndaainpj";
int dlraaq = 1098;
bool pewcrkeujjnse = true;
string zyknbinlc = "mepdzstdnqmiqsglxmqnabffhnkguyihwbtwlxnqsnfz";
bool btqosdmx = false;
double jrhpwaywye = 18066;
bool kphybpohrvogu = false;
string cbsfdujuiwqhtqr = "fde";
if (true == true) {
int gycfgcoye;
for (gycfgcoye=17; gycfgcoye > 0; gycfgcoye--) {
continue;
} 
}
if (false == false) {
int ciexkztfrl;
for (ciexkztfrl=6; ciexkztfrl > 0; ciexkztfrl--) {
continue;
} 
}
if (string("bhebxujbpvzuyhxhqeeuswbbancagbtusqsjmhpugyetulgcndaainpj") != string("bhebxujbpvzuyhxhqeeuswbbancagbtusqsjmhpugyetulgcndaainpj")) {
int mdulc;
for (mdulc=39; mdulc > 0; mdulc--) {
continue;
} 
}
return 62272;
}

double gkrtans::wcbzjrfrfxymyhogri(string wvcmyemthdgiboo, int pnwxbgubz, double kemie, bool qygfnnpdwovliy, string vezaybwb, bool tpfgkt) {
bool bdhvf = true;
string rlrvuoamgxwtod = "ckivpkrpzwprikxbbxymjkgoryhxbyzwigitktcwywakkajmwcsaitqzckxixnhhujxoebgevuo";
int ilqyjfyydrztvzw = 1052;
bool uzgvpbhcusw = false;
if (1052 == 1052) {
int kskrrg;
for (kskrrg=0; kskrrg > 0; kskrrg--) {
continue;
} 
}
if (string("ckivpkrpzwprikxbbxymjkgoryhxbyzwigitktcwywakkajmwcsaitqzckxixnhhujxoebgevuo") == string("ckivpkrpzwprikxbbxymjkgoryhxbyzwigitktcwywakkajmwcsaitqzckxixnhhujxoebgevuo")) {
int ryvygd;
for (ryvygd=27; ryvygd > 0; ryvygd--) {
continue;
} 
}
if (true != true) {
int ly;
for (ly=11; ly > 0; ly--) {
continue;
} 
}
if (true == true) {
int cxbbweck;
for (cxbbweck=4; cxbbweck > 0; cxbbweck--) {
continue;
} 
}
if (string("ckivpkrpzwprikxbbxymjkgoryhxbyzwigitktcwywakkajmwcsaitqzckxixnhhujxoebgevuo") != string("ckivpkrpzwprikxbbxymjkgoryhxbyzwigitktcwywakkajmwcsaitqzckxixnhhujxoebgevuo")) {
int sz;
for (sz=80; sz > 0; sz--) {
continue;
} 
}
return 95294;
}

string gkrtans::myydcoulznfjdqsvyrphc(bool bsjsurzumuna, int vtqqdgzchuedky, double getrznrqsax, string bzjrntgfm) {
double lmdzzuxijhl = 36563;
string ucpdprlz = "ohjxiqemcboxfppwudblzhvbmjhmuyaklkpsutuwa";
string guydwpgm = "ozjmfdsblipoyzunwzoldpgczcycqfibshfvwrmcxlan";
bool chkhkecekmuiue = true;
bool ssbjihlbv = true;
double iqlbhcqadcp = 64298;
bool symkdlydybvbd = false;
double aedlmil = 13977;
return string("fdyxup");
}

int gkrtans::hpdqnwbbrgwcglr(bool avytmxyp, int zemdiodoz, double jgbyrnifmpncmub, int dzkbb, int dfnhti, int jruzctqngfxljja) {
string jrsgbxpdhfrp = "klaseynqxdujkttuqpmjxjxteqepffxvneceg";
string wojcx = "dcedsdyfleujuhe";
string zmgcomrqgfymyp = "jpenwjljsorfbwmsq";
if (string("klaseynqxdujkttuqpmjxjxteqepffxvneceg") != string("klaseynqxdujkttuqpmjxjxteqepffxvneceg")) {
int ngucaztdxc;
for (ngucaztdxc=35; ngucaztdxc > 0; ngucaztdxc--) {
continue;
} 
}
return 38368;
}

int gkrtans::gnfdyglryaueyiexx(string xhqtthvfwjt, string uslbyusaqahyb, bool bevjqsm, string brtqwqaxo) {
string ocsnfoysquhf = "dlgebartlzdtxisbsqkgcsvenplwqytkgeupjyycztskvnytll";
string wasfeduravix = "cxsclbdjryuqujbanmintgxewglvd";
bool voxwyhowssg = true;
int nxouznwfam = 6068;
bool ityjwbwvwphqfuk = false;
string bmygqobkenanr = "sapedzshtlavrjwujmcyjx";
if (string("sapedzshtlavrjwujmcyjx") != string("sapedzshtlavrjwujmcyjx")) {
int jyjye;
for (jyjye=4; jyjye > 0; jyjye--) {
continue;
} 
}
if (string("dlgebartlzdtxisbsqkgcsvenplwqytkgeupjyycztskvnytll") != string("dlgebartlzdtxisbsqkgcsvenplwqytkgeupjyycztskvnytll")) {
int ynjomjlpc;
for (ynjomjlpc=38; ynjomjlpc > 0; ynjomjlpc--) {
continue;
} 
}
if (true != true) {
int hfzszu;
for (hfzszu=2; hfzszu > 0; hfzszu--) {
continue;
} 
}
if (string("cxsclbdjryuqujbanmintgxewglvd") == string("cxsclbdjryuqujbanmintgxewglvd")) {
int whqonzzp;
for (whqonzzp=2; whqonzzp > 0; whqonzzp--) {
continue;
} 
}
return 8008;
}

bool gkrtans::cqltpgggomkzbmh(bool nmwzskvlsuzarf, bool naeldjevwpt, double xqqafyd, int wgafzdz, int pawiuvilpa, int hcqjmjmr, bool ghsmejqchhc, int evvlrormpjzdb, string wqmblqxfxksu) {
int zfxjkmu = 4806;
double qbvdinueuzgd = 19018;
double ypzrwexr = 73361;
string dhnaqmbyp = "bcftlnszsgwuvpcymirutcxasbceglxyaikglwwvmeyowxzelnzmwqajludopbvvntjrfmcjvoscmqec";
if (19018 == 19018) {
int wkznmjv;
for (wkznmjv=24; wkznmjv > 0; wkznmjv--) {
continue;
} 
}
if (19018 != 19018) {
int rcdebnqhbi;
for (rcdebnqhbi=29; rcdebnqhbi > 0; rcdebnqhbi--) {
continue;
} 
}
if (string("bcftlnszsgwuvpcymirutcxasbceglxyaikglwwvmeyowxzelnzmwqajludopbvvntjrfmcjvoscmqec") == string("bcftlnszsgwuvpcymirutcxasbceglxyaikglwwvmeyowxzelnzmwqajludopbvvntjrfmcjvoscmqec")) {
int dbedwzm;
for (dbedwzm=73; dbedwzm > 0; dbedwzm--) {
continue;
} 
}
if (4806 == 4806) {
int ab;
for (ab=29; ab > 0; ab--) {
continue;
} 
}
return false;
}

gkrtans::gkrtans() {
this->cqltpgggomkzbmh(true, false, 12078, 2018, 7145, 2903, true, 448, string("yanxfqwkthgrgehofvoljcj"));
this->jfbkurbddifldbowqqwrlpyyt(false, false, string("kdbjnydvqbhjudvtstciqhjpymeizuofsvacmzzajqutaxnntcpmsgluwzbjeiiavjazltzkwkayzchdbmbx"), 5041, 25098, false, 16578, 725, true);
this->wjvincbzoqedezedafersdz(5044, 1013, true, 3030, string("nepuzfluhgnpjhfozkpxxfddykyidxealghcgbmkvlkhcwmdtddlxzqtlfnvksywwylfyxemiliju"), false, string("dvrcspdaqdiubtynatexigpgfdgnplxcxtxaxwnkksekgehpvipsvvrcpbeoraivzosuurlhstarquhsamgrznxdxzicrqxlaecb"), 2326, 3390);
this->riigsdcuvrpj(string("swhjtmjuytnmxhbzysqnmqsu"), string("ykjblgibxyvhofzamssauubaspoqaasbbdjavtfldzpsowjuluuffqkvgprfgobzwshjsnlwsinhqaqzbk"), string("dtltrgapswdstbxb"), 1234, 4752, 32574, 3291, false, false);
this->xkiogdizswvbjeosb(57725, string("zdvipglpctsyttrwyoyymceiyudvaspimnwyrsvvrivuykxoooqqxflt"), 4381);
this->sikyobmddaw(2938, 16074, 5793);
this->arpuzbdoootdrfelz(true, 22309, string("gavxbjlrvjhyxnjuqnatn"), string("pkowatjekeimdaqcybdqiqzudpunsodtprvxnykqtntmklolatupthnzjxffaqrshjlbqdm"), 287, 536, false, 2385, false);
this->wcbzjrfrfxymyhogri(string("iehemmpkwbikalstppoffodcycmenoxweuhytqisphhwaezcxyohaecdgyauqcazzvdmnbjcfvyisdmtuywqcinn"), 7205, 3188, false, string("chrhhzbcwnycuopnrpbflvq"), true);
this->myydcoulznfjdqsvyrphc(true, 2878, 30050, string("trpurtgwqhuajyqvfdynrbrmykzromzkkoksneoqhhegmfzygjaqkvdlwrjw"));
this->hpdqnwbbrgwcglr(false, 3000, 1843, 2560, 6712, 2343);
this->gnfdyglryaueyiexx(string("hyoxlufadhalvypkyeveth"), string("qseiqqrgcamerzlgjneugpfseppokkyxzcjhzbsadanmjgcghaktjqa"), false, string("zharklvflqnxhvirsoyskrnxqmnvcscpbzrezygiuzifnfwlqmlfehnfoikywrsgjjsxwuhshriwaipnvjejiocz"));
this->eizopimjkvuafindvhd(419, string("atpkvyqiczfwkp"), 3209);
this->sifcowusubmvjxm(5430);
this->lsmzzhleic(string("fwfmmgzojwdvparwsrxwrqakohwmhvxgufjdlovzxdnjucfsfdpzxnrdmh"));
this->ructeclrklwssyz(string("qygheqwhgnwrkrotabzziiqaotmmjadhiokkfqwimyrmtjuhjobyna"), 13897, false, 2773, 5316);
this->tqtpuhceejsldxbcoosndkd(50932, true, string("ufgtjxxtzagqggengiarkycqeklgrbijryvswuzhvjdnyahfwelkddxxedzvehtaptdsgrezhaj"), 2420, string("ynudvsaqxfiegbxawbotawzhqposjngzwxappevldgiqcwcuegufawrwditpwmkuq"), 79675);
this->vwskczyfdysmoevowklwszmhh(string("yihawunajiivzimhpklvrikbrdasnxvpsowvzcgqtebicbkjnlsjifetwfyiq"), 723, 449, 4945, string("aeytilpvbchwmfvqxebzgllsjupcqbjqewcxwgfsubaosdlyjulczqao"), 19364, false, 41734, 905);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ooajbtc {
public:
bool fpggdrqbs;
ooajbtc();
bool pcrenaduttntkoaedyb(double mchyqtwyw, int ilzgcpxuhzbgok, bool inyfep);
string gkolruejnirnzqjzwpta(bool gyvhnvtaeppgt, string vgaszfqjg, bool tuezbjjsaemmnym, double kirdsjbadyfhc, bool gmxyxtvbebx, double xjornshpzegbr, int htiqyhedbrwdf, int dvaax);
string tcktljggukpq(double ldweeqas);
string oakeatuyuvt(int ywzjlijkgchslib);
double hqpcadbuyqoyfzvvwfm(bool kowtnohogl, double cllaoaebuqbhwd, double nglyjfntrwqwr, string sqckymxb, int zxzecpdlfku, int cyoqtiszgrisot);
int rreyiaquliltnmmqenms(string opjybghug, string olubm, bool ysusvnetlusho, double qadzobcb, double mgiovxc, double uftpdmygvebv);
string izsglhomxzbfacoqalbl();
void lqibiycutdwznjmbpdb();
void uxaitfuegzspkfurycurufdnk(double jfyurysmgvrs, double iqlntykruqczw, string fimxy, double vlkkzvvwnw, bool jyawr, double xejjt, string glltcbej, int vqhzeewgdvju);

protected:
double gmwsbklulhgtab;
string iihdddmsgp;

int mugbvhwkgxikzugnl(double oatygbhptkgnu, double nfxbfdmf, bool ynrlzlucqwumxey, bool lwishxdcwvrymy, string nkwjukllbpldy, string gmrtldtfpnnhry);

private:
int jxwvv;
double sguly;
bool ngxyphb;
string nifmxycjy;
bool ttixsmleyal;

bool ddisadytxjm(string rgwwgpdxetjtnfu, string jlignhu, string jquqrgdfsxsxecg);
double bwvnpvpxwqghbchigbnedja(string vhihpua, string hlqlyvlf, double mfxzziminibg, int swxsbmcapt, int odgogdhe, string huhwhwqbce);
void qyecxufgblcistqraz(int wlanzqe, int rxgbtapj, string jylmuqviexbg, string mghwl, double trdlw, int aokycwdp);
int uwmuzpohmgrhv(double aeuivnwgjwfiin, double vwnmxeu);
bool zdcbydjkadxqkgupadf(double kxlbqsrqiqvwp, double bjircfhlrn, int txqdwkcgtiqpz, string quftrkxtetlj, bool qbwqmrzqdsl, int xipolvzhnklyd, bool qioypmigwui, double ysgzyygpzcrzuib, string hepjjeqawvctan);
void llgwqrzmoiptrvmxbn(int vjlccpck, double aijkwjawimbzvx, double fivzfkjjhanwzzu, string dacxpfg, bool zoyyzt, string aeulgbjhkobevb, string kdlspet, bool rknijvd);
bool bxfwclstjkcbt(int maskjlsv, bool qnuodhdtwkgzz, string pqmmpq, bool mlpru, bool ovjtehejvugqeel, string wmpxnlsixf);

};




bool ooajbtc::ddisadytxjm(string rgwwgpdxetjtnfu, string jlignhu, string jquqrgdfsxsxecg) {
double shatiuystbcjg = 69949;
bool mssrjeza = false;
double uswiudiz = 38067;
int osibfjypbzjqp = 1842;
string mqjomehefd = "yuzhflzeqkgavjsckipboyrpvdrgifmdhxqcaytuqybnjnrgrnzwemqvxupjnrdwykmrpnmgmbsjhmeewck";
double npldunriuxirvcx = 50327;
string vsbbbypa = "uyozvsajsatwhtjbhzfcmtuhnztwvazdukmoxjykryiypidanairr";
string ihztzxpei = "vdzhtkniknjkkbzugmhybntdfpsaysh";
return true;
}

double ooajbtc::bwvnpvpxwqghbchigbnedja(string vhihpua, string hlqlyvlf, double mfxzziminibg, int swxsbmcapt, int odgogdhe, string huhwhwqbce) {
bool uqlvuj = true;
double samveolwora = 8173;
int ubbldmngkzr = 1714;
bool meyevcfsgwmsdq = true;
double txqtugbh = 10293;
bool qplofggb = true;
bool oxwdtvnigsmxn = false;
int zmijyaiuzs = 1529;
return 74589;
}

void ooajbtc::qyecxufgblcistqraz(int wlanzqe, int rxgbtapj, string jylmuqviexbg, string mghwl, double trdlw, int aokycwdp) {
int kuopypjdwwqjjnu = 1034;
string gsrbqfwmbbhb = "dnwcyljjnubsgtpaukgwlucvxxehffnerjhibzsgbipdswdrmkwffvegglfgtxobrffoofooavfbjceahcinnvqsebrlryueuve";
double ubpvdynws = 32416;
int wcvbfuudhojzvzc = 2144;
string mcfaxvkz = "bjsvgiycobfohqywqjviaukdkfemfehaoshjbglemwtlzwkpteaimhdrdf";
double wkeztvigikh = 29164;
double xuqnlasssoojnv = 43310;
double nnumoj = 19884;
if (2144 != 2144) {
int dvol;
for (dvol=97; dvol > 0; dvol--) {
continue;
} 
}
if (1034 == 1034) {
int rfkjm;
for (rfkjm=86; rfkjm > 0; rfkjm--) {
continue;
} 
}

}

int ooajbtc::uwmuzpohmgrhv(double aeuivnwgjwfiin, double vwnmxeu) {
bool rasymhgmv = false;
if (false == false) {
int iapucm;
for (iapucm=76; iapucm > 0; iapucm--) {
continue;
} 
}
if (false != false) {
int jerjrdejm;
for (jerjrdejm=58; jerjrdejm > 0; jerjrdejm--) {
continue;
} 
}
if (false == false) {
int bj;
for (bj=56; bj > 0; bj--) {
continue;
} 
}
return 35262;
}

bool ooajbtc::zdcbydjkadxqkgupadf(double kxlbqsrqiqvwp, double bjircfhlrn, int txqdwkcgtiqpz, string quftrkxtetlj, bool qbwqmrzqdsl, int xipolvzhnklyd, bool qioypmigwui, double ysgzyygpzcrzuib, string hepjjeqawvctan) {
string rfqijhqupka = "zxnirgnogwuxmpearbekecneykyfavgqeeditbckvooergcvhwajimvihdkvqtspgdpathjnegkrxlwymvtevw";
bool rabkm = true;
double gmirayqxgqpx = 9474;
double cqcspvb = 16408;
if (true != true) {
int xsemzpdpjt;
for (xsemzpdpjt=86; xsemzpdpjt > 0; xsemzpdpjt--) {
continue;
} 
}
if (16408 == 16408) {
int dxx;
for (dxx=10; dxx > 0; dxx--) {
continue;
} 
}
return true;
}

void ooajbtc::llgwqrzmoiptrvmxbn(int vjlccpck, double aijkwjawimbzvx, double fivzfkjjhanwzzu, string dacxpfg, bool zoyyzt, string aeulgbjhkobevb, string kdlspet, bool rknijvd) {
string psvypxmazcrv = "shavqdgnqpjvgkbvneuqtyizavqru";
int betja = 6991;
bool hidhzlz = false;
if (6991 == 6991) {
int pxxprhzewg;
for (pxxprhzewg=82; pxxprhzewg > 0; pxxprhzewg--) {
continue;
} 
}
if (6991 == 6991) {
int nqayolfi;
for (nqayolfi=15; nqayolfi > 0; nqayolfi--) {
continue;
} 
}
if (string("shavqdgnqpjvgkbvneuqtyizavqru") == string("shavqdgnqpjvgkbvneuqtyizavqru")) {
int qqzntohto;
for (qqzntohto=72; qqzntohto > 0; qqzntohto--) {
continue;
} 
}
if (string("shavqdgnqpjvgkbvneuqtyizavqru") == string("shavqdgnqpjvgkbvneuqtyizavqru")) {
int xhvacbk;
for (xhvacbk=67; xhvacbk > 0; xhvacbk--) {
continue;
} 
}

}

bool ooajbtc::bxfwclstjkcbt(int maskjlsv, bool qnuodhdtwkgzz, string pqmmpq, bool mlpru, bool ovjtehejvugqeel, string wmpxnlsixf) {
int rkrvaihazmj = 2104;
double ppcscwwarl = 49963;
double qsihqerl = 22915;
int zipdl = 4156;
double kctsvrlmuwv = 85614;
if (22915 != 22915) {
int qxfmz;
for (qxfmz=41; qxfmz > 0; qxfmz--) {
continue;
} 
}
if (2104 != 2104) {
int wseaijm;
for (wseaijm=27; wseaijm > 0; wseaijm--) {
continue;
} 
}
return true;
}

int ooajbtc::mugbvhwkgxikzugnl(double oatygbhptkgnu, double nfxbfdmf, bool ynrlzlucqwumxey, bool lwishxdcwvrymy, string nkwjukllbpldy, string gmrtldtfpnnhry) {
bool tbfnjkrghat = false;
int cjwivyxyrgghebw = 452;
string etecb = "jyigmbsqlvrwwffagrxgknwikpxsmcazvgtibbrvcvw";
bool xdptsp = true;
double livadivhqwnz = 22375;
bool lfsmol = true;
bool hehconqyafdzfju = false;
string dinukdfxcby = "rgvcppjvnysprbswpdsolpmusbeoqcweugvx";
double xyenqlhq = 45390;
if (true != true) {
int qmcidzx;
for (qmcidzx=38; qmcidzx > 0; qmcidzx--) {
continue;
} 
}
if (true != true) {
int psgsrjxy;
for (psgsrjxy=52; psgsrjxy > 0; psgsrjxy--) {
continue;
} 
}
if (false != false) {
int bicw;
for (bicw=90; bicw > 0; bicw--) {
continue;
} 
}
if (false == false) {
int xpjk;
for (xpjk=8; xpjk > 0; xpjk--) {
continue;
} 
}
if (false == false) {
int qldmxlat;
for (qldmxlat=8; qldmxlat > 0; qldmxlat--) {
continue;
} 
}
return 18366;
}

bool ooajbtc::pcrenaduttntkoaedyb(double mchyqtwyw, int ilzgcpxuhzbgok, bool inyfep) {
int mnjgcvpc = 510;
int ksmoobhlag = 2118;
string efhvx = "ydeawqrhdumqhfeucopvrdalbhqdsoavxtlt";
int qcoekqinwqfepwd = 5743;
string brlxrj = "want";
bool ugvcablordyix = false;
int jbjfkufnjmxzpr = 5054;
int wmzrfibdujprt = 175;
int hvjjftnmlyre = 7743;
double cbngpetpthfuwvv = 92400;
if (5743 == 5743) {
int sscziobdzu;
for (sscziobdzu=54; sscziobdzu > 0; sscziobdzu--) {
continue;
} 
}
if (string("ydeawqrhdumqhfeucopvrdalbhqdsoavxtlt") == string("ydeawqrhdumqhfeucopvrdalbhqdsoavxtlt")) {
int ge;
for (ge=55; ge > 0; ge--) {
continue;
} 
}
return false;
}

string ooajbtc::gkolruejnirnzqjzwpta(bool gyvhnvtaeppgt, string vgaszfqjg, bool tuezbjjsaemmnym, double kirdsjbadyfhc, bool gmxyxtvbebx, double xjornshpzegbr, int htiqyhedbrwdf, int dvaax) {
double rwstjc = 3873;
int sbgezpzmomltdk = 233;
if (233 == 233) {
int gewiude;
for (gewiude=89; gewiude > 0; gewiude--) {
continue;
} 
}
if (233 != 233) {
int ivsastb;
for (ivsastb=54; ivsastb > 0; ivsastb--) {
continue;
} 
}
return string("jdajprsjw");
}

string ooajbtc::tcktljggukpq(double ldweeqas) {
int paqznfm = 1140;
int iybgcogiafma = 188;
double vsbkgdiuasi = 29235;
string ljdmvoseto = "akzpwebkyhxugnpkiyhaopexb";
if (188 != 188) {
int vykoci;
for (vykoci=100; vykoci > 0; vykoci--) {
continue;
} 
}
if (1140 == 1140) {
int zcccf;
for (zcccf=5; zcccf > 0; zcccf--) {
continue;
} 
}
return string("bzrlsqhfsqvte");
}

string ooajbtc::oakeatuyuvt(int ywzjlijkgchslib) {
bool nyxrylsvdwwb = true;
string mgsrirn = "rqcesmeswhxqbpfztmdqzbjppohnffkhvqbdoxkzv";
double ucqimrrbggp = 14847;
bool kauzwvfnramdpw = true;
double lnijcfmqrgiak = 27130;
double ccvxjpikjfxcc = 1330;
int zaybdnuez = 1966;
int yrewnscabk = 3031;
double jilgjdtzsygwd = 38404;
int anlmpdlzsfapork = 542;
return string("rfsugb");
}

double ooajbtc::hqpcadbuyqoyfzvvwfm(bool kowtnohogl, double cllaoaebuqbhwd, double nglyjfntrwqwr, string sqckymxb, int zxzecpdlfku, int cyoqtiszgrisot) {
bool gzqnwv = true;
string dbzymjqxmnhadq = "syiueuazflijzdmankbc";
bool ghukodtkdlhipa = true;
bool lrmcyn = true;
if (true == true) {
int jxdrvz;
for (jxdrvz=96; jxdrvz > 0; jxdrvz--) {
continue;
} 
}
if (true != true) {
int wdj;
for (wdj=53; wdj > 0; wdj--) {
continue;
} 
}
if (true != true) {
int adfoxvq;
for (adfoxvq=81; adfoxvq > 0; adfoxvq--) {
continue;
} 
}
return 616;
}

int ooajbtc::rreyiaquliltnmmqenms(string opjybghug, string olubm, bool ysusvnetlusho, double qadzobcb, double mgiovxc, double uftpdmygvebv) {
int gfzyzbisy = 466;
string jgwxhgybiyq = "u";
bool nyxvhlzapxpam = true;
bool ixhboeewuwdexwm = false;
if (string("u") != string("u")) {
int igufvxz;
for (igufvxz=71; igufvxz > 0; igufvxz--) {
continue;
} 
}
if (false == false) {
int icnrw;
for (icnrw=44; icnrw > 0; icnrw--) {
continue;
} 
}
if (true != true) {
int rpftlyozv;
for (rpftlyozv=76; rpftlyozv > 0; rpftlyozv--) {
continue;
} 
}
if (false == false) {
int yrzuhvd;
for (yrzuhvd=56; yrzuhvd > 0; yrzuhvd--) {
continue;
} 
}
if (string("u") != string("u")) {
int ttdbajk;
for (ttdbajk=27; ttdbajk > 0; ttdbajk--) {
continue;
} 
}
return 60214;
}

string ooajbtc::izsglhomxzbfacoqalbl() {
string ydflkjcuevbpehq = "onbzfqaifspgbhgqfrhdmyedluaibhyhbnzsoryxvnfkizsukeehstityhosbpnyobzcirdjmcxatcywaco";
int jgdnujqwrj = 1307;
bool ynqfmkdbxdbup = false;
return string("gb");
}

void ooajbtc::lqibiycutdwznjmbpdb() {

}

void ooajbtc::uxaitfuegzspkfurycurufdnk(double jfyurysmgvrs, double iqlntykruqczw, string fimxy, double vlkkzvvwnw, bool jyawr, double xejjt, string glltcbej, int vqhzeewgdvju) {

}

ooajbtc::ooajbtc() {
this->pcrenaduttntkoaedyb(51615, 5056, true);
this->gkolruejnirnzqjzwpta(true, string("jqhhhvmfulhldsztkdbudhudixcjcbyuewpotjxuutvwdirbtlzryysbhnpfxodublmkpgvtnblnn"), true, 72356, true, 395, 2774, 519);
this->tcktljggukpq(74811);
this->oakeatuyuvt(3198);
this->hqpcadbuyqoyfzvvwfm(false, 24802, 50404, string(""), 2678, 4333);
this->rreyiaquliltnmmqenms(string("nfwqijuvcegerregvgwvbijzzixthwzdavnbvmnqrimhzthoth"), string("lxtgdjtwcsboqkcrxbcbqxrfuhbcovybjwdyrnpehfzvdnrrcvpnqlyxdnbsrmrexyyjmkrrvqoyezrkravgbmcmnl"), true, 1839, 18574, 6803);
this->izsglhomxzbfacoqalbl();
this->lqibiycutdwznjmbpdb();
this->uxaitfuegzspkfurycurufdnk(13554, 7292, string("gvoagrhtcxrvofolkmwfpazpzllrdsz"), 58621, true, 70253, string("hmqrhgqghtzutwhrihfujufqnnntxpyavyte"), 4774);
this->mugbvhwkgxikzugnl(19702, 83874, false, false, string("uisizbafyumgknrhtdmqieyoxkcoajartwdbqegcejlqdfugumsl"), string("ehpvpyk"));
this->ddisadytxjm(string("cuptcpwgjoaklrbsgkwgmpyztmdfdasksqmmmivefmrrzisrefmxmpssvcdzjnfsgxoelinkplccwdhlcoajpicimgltqdn"), string("lhqkpfdwiiwuxnmsprhcpysvhqhthwwhnlocjlgbbuejypwyqahtoezlogabfoyetvfcqdbgiunecbwllsfnzfjrxkntoiyxor"), string("jbxxlwcpgmhultszhftqvkuaafsqkvwviab"));
this->bwvnpvpxwqghbchigbnedja(string("nbtrlimjscaixcruyepixhrmcrouxfrlzluqaabtpabxksy"), string("ycxzlrsecgncnhddqpdgpnrucsfkakzwfpspyukvansvfmjehqgnfhdiilcetmloaqmvedznnovvlfifqpbgauzqacwdquuhfttn"), 4907, 2588, 811, string("kwgmmkcwkkwpbdnymkxxzjdxngdabtgcxphgvfvjiiukkxsfabstlmwltyxjbksbxuxoqrmzxycihwcz"));
this->qyecxufgblcistqraz(2953, 6653, string("lluteabdkpbgonjhzavkozxutrseikmh"), string("cekqznwayqgxmotlaalvdjoocdvbcnl"), 9022, 1641);
this->uwmuzpohmgrhv(6856, 26658);
this->zdcbydjkadxqkgupadf(64193, 27126, 1781, string("rkrjifcdvdgtfavwxrrxzuxqdzlttiaqibybtlcwcjn"), true, 3033, true, 34210, string("ucymmthpbglhjaospmrahegcjvfphebytyldzskcnifwrszvxcpqzpdg"));
this->llgwqrzmoiptrvmxbn(429, 47513, 90818, string("tzmuuvqegvxzmdjixcwxxhkijoclyjuhyibhdbsetuhfd"), true, string("fipjfzlmkmjbqbeuwxwivfxlectminkuxfqfedfhveppkdtjorakjvnwisltqdcmokozszwvfok"), string("sadibpypvcuvyubnc"), true);
this->bxfwclstjkcbt(161, false, string("ucxvywcxgowelegrdnoepyndolgeftbsgjylbvmykmbghfolhjnidgk"), true, false, string("hhvfwgarhcxkywjozyxkeolclxmx"));
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class lugphsh {
public:
int emvugqdeykz;
double tjblhk;
int ewuddnbgwqfqmrz;
bool jxucvy;
double cfjursvtadxsrv;
lugphsh();
string mtewoxymaqyfanuy(string tzkfbpcrjrtspma, int qjvgrceszquns, string zyudhvf, string snhuxfi, double thcwefqvh);

protected:
bool iygpmisek;
int vknuzviypc;

double aizepumlefyo(bool ngmbjmipcco, bool pgkepbyvqkvbiv);
int zbtednccepeobdelswvsddxit(int svnkpwnkrxodvho, double sazdkxwojecdrc, string ykbxpd, double qvtbdfxvv);
bool dfojzmlwudv(string kdrkbvttz, int wkldjaasik, double dpkvbyxqf);
int nhutxiotaxdauflgiikc();

private:
double ptptd;
string uozddyjagysv;
string zrwpdbcynvbss;

string vxcqhcyinaxisbnvaijg(double habqeeylbxym);
int znaqhxtemegnaphmxems(double vqpzujr, int uegbyq, string udcfocpmc, double mtfsa, int wxjcr, int cbixwyk, bool lotooevzx, int ahzfkqrdaxife);
double xdewkzqfdexcvhstuwyy(int yygibi, double zzmdf, int ofjvlfxqvgdyuwp, bool zuqxdiksh, string dxrhbpjrekvsxm, string gzdcmkhri, bool ufgkhxzmlyd);
int uektkapecxaytbrrxa(string ghoajm, string cgclxtcjqs, string lvuji, string gimmndqa, int nfeejskqojbmt);
int bgdstooravjdaxf(bool arfkhwhxrlhzt);
string qeuqrzyauheyxoyg(double ivobeywk, string mcejsqveicv);
double mwndtalfalcqzrvwpcvir(int rizmosbcey, bool zlmdwg, double oitarwyrwpp, string qccfqdyyya, bool mfxypssjxvwdmhh, int ughilpsyyubjv, int dqdaorterfzayqq, bool xgtqtvbfqkntqf, string tnhkncrnpml, bool famqtemxfisq);
int izlqubzmfigaikvbtixz(double iadtxy);

};




string lugphsh::vxcqhcyinaxisbnvaijg(double habqeeylbxym) {
string dlihggjx = "xnrpttikzzzhsxsorqsmnrdcobuwtxlmdmrg";
int srqbeuj = 7018;
int rxsiopznflzgt = 2706;
string dbknzyrzbolcic = "hzjulwurdvlgblxzhwiuxhswdurqgwxdlqantkruvyscldsdyqdtcaztxbryshqxrqmjlxcdblcqprsjyncrbmzz";
bool qffcvmwqnvhmnnq = true;
int cxvnwnetwrvyyy = 2996;
bool inehnsjmycwkv = true;
string erljhj = "copvlxdvucoskajwfltiwqsnacjyemweiikvjihifhanmzjyauzvxzgzj";
int rdjcson = 947;
if (string("copvlxdvucoskajwfltiwqsnacjyemweiikvjihifhanmzjyauzvxzgzj") != string("copvlxdvucoskajwfltiwqsnacjyemweiikvjihifhanmzjyauzvxzgzj")) {
int lyvqxcu;
for (lyvqxcu=28; lyvqxcu > 0; lyvqxcu--) {
continue;
} 
}
if (2706 == 2706) {
int cvguepkzbc;
for (cvguepkzbc=57; cvguepkzbc > 0; cvguepkzbc--) {
continue;
} 
}
return string("kqusoacraqce");
}

int lugphsh::znaqhxtemegnaphmxems(double vqpzujr, int uegbyq, string udcfocpmc, double mtfsa, int wxjcr, int cbixwyk, bool lotooevzx, int ahzfkqrdaxife) {
int ssiiklioeyl = 1169;
int yyfiostyppani = 2461;
string dmufbyzae = "rqeugmsucttoumkwjubpfhrsrhislppabzxiqlmejlkgahrtohxkawiprojooeusaqnaavym";
double vijfrmkpzb = 4232;
int icloia = 3306;
string xhrqvxcmmcuvlge = "gdrbknpzxnacihzokghoruyxszfjhmqrbikvrgwgrhiuuwhlscnbeatutkhyqiuxulzsrlvrvvbupmf";
string nommtbhopb = "zrnluwdlezlsimimomfwxqfwim";
double bynjlfsu = 12869;
string rqoreflanzzbnel = "cwqirpciqlgydwgqtdshhnppqehdbzvaecyusguljqdyhjmhkvoepeijgpfibnlrgtcpxgpkytljqmojzhvkmgz";
if (3306 != 3306) {
int edbzvlh;
for (edbzvlh=33; edbzvlh > 0; edbzvlh--) {
continue;
} 
}
return 53149;
}

double lugphsh::xdewkzqfdexcvhstuwyy(int yygibi, double zzmdf, int ofjvlfxqvgdyuwp, bool zuqxdiksh, string dxrhbpjrekvsxm, string gzdcmkhri, bool ufgkhxzmlyd) {
int dxpwtaymsio = 1062;
string rluiuhemvvcax = "fctpqzedib";
bool pdikhrsmkf = true;
int xnptdlsffso = 1502;
int fpjfjf = 4377;
int xnkevp = 2157;
bool ythtqkkotwyw = false;
return 96398;
}

int lugphsh::uektkapecxaytbrrxa(string ghoajm, string cgclxtcjqs, string lvuji, string gimmndqa, int nfeejskqojbmt) {
bool dsktkgysqqox = false;
bool pqrdpqfsaoiwv = true;
if (true != true) {
int fmztlxir;
for (fmztlxir=43; fmztlxir > 0; fmztlxir--) {
continue;
} 
}
if (true == true) {
int bvruomor;
for (bvruomor=10; bvruomor > 0; bvruomor--) {
continue;
} 
}
if (false != false) {
int jbu;
for (jbu=58; jbu > 0; jbu--) {
continue;
} 
}
if (false == false) {
int qxikmelt;
for (qxikmelt=11; qxikmelt > 0; qxikmelt--) {
continue;
} 
}
if (false != false) {
int vzutv;
for (vzutv=14; vzutv > 0; vzutv--) {
continue;
} 
}
return 45895;
}

int lugphsh::bgdstooravjdaxf(bool arfkhwhxrlhzt) {
bool pwcoqbsq = false;
int japigbmnwoam = 1083;
string ynovtx = "ugvaarcc";
int zbgefdmo = 1319;
string vblazvhzegksg = "ienjpldlmpmjhajubdrarzhsqbxokiwlseildqrtfrnbfkyywfyzdkngsqdthykhkmopeoisgaupowclbnuifq";
bool mrcfcr = false;
double skjueczxsq = 53278;
if (53278 == 53278) {
int ni;
for (ni=1; ni > 0; ni--) {
continue;
} 
}
if (1083 != 1083) {
int ubsv;
for (ubsv=34; ubsv > 0; ubsv--) {
continue;
} 
}
return 86672;
}

string lugphsh::qeuqrzyauheyxoyg(double ivobeywk, string mcejsqveicv) {
double cvkkkc = 69354;
int othfeatffreyj = 468;
bool tqghjtifgqgbruq = false;
int ajspikysjpgowxu = 915;
double taayvcdlvvjmso = 13873;
int yzjsaziqkrhhnnp = 8316;
double xohkwcbk = 35201;
string uncbtwsg = "pvigsizkgoj";
string hbljqmey = "rcumwaifezhdksgy";
if (468 != 468) {
int dtis;
for (dtis=100; dtis > 0; dtis--) {
continue;
} 
}
if (string("rcumwaifezhdksgy") == string("rcumwaifezhdksgy")) {
int juxdoqoz;
for (juxdoqoz=73; juxdoqoz > 0; juxdoqoz--) {
continue;
} 
}
if (13873 != 13873) {
int cgdjtxhtd;
for (cgdjtxhtd=41; cgdjtxhtd > 0; cgdjtxhtd--) {
continue;
} 
}
if (468 != 468) {
int vzu;
for (vzu=37; vzu > 0; vzu--) {
continue;
} 
}
return string("emaayjiegwsaeulfxe");
}

double lugphsh::mwndtalfalcqzrvwpcvir(int rizmosbcey, bool zlmdwg, double oitarwyrwpp, string qccfqdyyya, bool mfxypssjxvwdmhh, int ughilpsyyubjv, int dqdaorterfzayqq, bool xgtqtvbfqkntqf, string tnhkncrnpml, bool famqtemxfisq) {
bool duyaemyxu = true;
bool uvjdwtde = true;
bool igbyzqhvcnbr = false;
double hfvyygs = 48901;
string mqqpqhoafpsel = "skcwwmszbbkzscuzcmwrqxysmbzpmywiir";
double nxpod = 36824;
string ixvay = "vgmlwiwqvqmjeinkylnnlmswsaixbgspsjhemqfwbxrmwpdlekaoztvyzpmzqmsnpgnntnovzihpgbfdiygikhbqjqexqmd";
bool yonlfrydzgxpg = true;
bool umdlmpx = true;
if (48901 == 48901) {
int dvr;
for (dvr=76; dvr > 0; dvr--) {
continue;
} 
}
if (true != true) {
int bpgxh;
for (bpgxh=89; bpgxh > 0; bpgxh--) {
continue;
} 
}
if (true == true) {
int neuxyvmt;
for (neuxyvmt=57; neuxyvmt > 0; neuxyvmt--) {
continue;
} 
}
if (string("skcwwmszbbkzscuzcmwrqxysmbzpmywiir") == string("skcwwmszbbkzscuzcmwrqxysmbzpmywiir")) {
int zovutwuvxn;
for (zovutwuvxn=38; zovutwuvxn > 0; zovutwuvxn--) {
continue;
} 
}
if (true != true) {
int licawfxjih;
for (licawfxjih=23; licawfxjih > 0; licawfxjih--) {
continue;
} 
}
return 99988;
}

int lugphsh::izlqubzmfigaikvbtixz(double iadtxy) {
return 20173;
}

double lugphsh::aizepumlefyo(bool ngmbjmipcco, bool pgkepbyvqkvbiv) {
int dgigfuilyqsy = 3813;
bool gbjjd = false;
int jpolonnv = 9340;
bool waxqvzvlyndh = false;
bool ycbmdasotvafns = true;
bool bexcfbqmdqbkilq = true;
bool ktkukxqayuay = false;
double sgiwooi = 30521;
if (false != false) {
int ngetkmuabt;
for (ngetkmuabt=44; ngetkmuabt > 0; ngetkmuabt--) {
continue;
} 
}
if (false != false) {
int baulryhgp;
for (baulryhgp=94; baulryhgp > 0; baulryhgp--) {
continue;
} 
}
if (false != false) {
int djopygpra;
for (djopygpra=98; djopygpra > 0; djopygpra--) {
continue;
} 
}
if (true == true) {
int fnahfcqqe;
for (fnahfcqqe=74; fnahfcqqe > 0; fnahfcqqe--) {
continue;
} 
}
return 17725;
}

int lugphsh::zbtednccepeobdelswvsddxit(int svnkpwnkrxodvho, double sazdkxwojecdrc, string ykbxpd, double qvtbdfxvv) {
string lavdxpepthsmsg = "rodzqqlopaczjhxsfnunmgyqyibrfqhxvokqhmnsoguktssylpovsztsrkbhpflhofzkqjfzvej";
int gcfsetx = 701;
bool qtsmhmsaxcfkixx = true;
return 99244;
}

bool lugphsh::dfojzmlwudv(string kdrkbvttz, int wkldjaasik, double dpkvbyxqf) {
bool ivucvykb = true;
if (true == true) {
int tlvcodqiea;
for (tlvcodqiea=55; tlvcodqiea > 0; tlvcodqiea--) {
continue;
} 
}
return true;
}

int lugphsh::nhutxiotaxdauflgiikc() {
int xpdumvxhpvkzoq = 1336;
double jobaa = 9688;
double kskjhskynjdt = 28014;
if (1336 == 1336) {
int xavg;
for (xavg=21; xavg > 0; xavg--) {
continue;
} 
}
if (28014 == 28014) {
int zyyeqftsao;
for (zyyeqftsao=45; zyyeqftsao > 0; zyyeqftsao--) {
continue;
} 
}
return 89309;
}

string lugphsh::mtewoxymaqyfanuy(string tzkfbpcrjrtspma, int qjvgrceszquns, string zyudhvf, string snhuxfi, double thcwefqvh) {
string haumoc = "trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia";
if (string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia") == string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia")) {
int rw;
for (rw=97; rw > 0; rw--) {
continue;
} 
}
if (string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia") != string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia")) {
int klbtt;
for (klbtt=37; klbtt > 0; klbtt--) {
continue;
} 
}
if (string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia") != string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia")) {
int idjponzg;
for (idjponzg=55; idjponzg > 0; idjponzg--) {
continue;
} 
}
if (string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia") != string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia")) {
int qwopazstjq;
for (qwopazstjq=58; qwopazstjq > 0; qwopazstjq--) {
continue;
} 
}
if (string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia") == string("trntyfdbevpyqzfwotrgnulpjxlvvmskkpfdfeltzqpllcsshwznttvyjhqfzygckkzia")) {
int dincvt;
for (dincvt=63; dincvt > 0; dincvt--) {
continue;
} 
}
return string("bctswjskevrwi");
}

lugphsh::lugphsh() {
this->mtewoxymaqyfanuy(string("tqletqyskhwaoyhwnhtfvqkxhgwbduobslczsjwbxryx"), 6574, string("bzytkxfozuztfdcccgcbojdipmrphultsqwmkdfarac"), string("qrewrfocvxaksnlkycysatfhibqfihemrdihjbx"), 27351);
this->aizepumlefyo(true, false);
this->zbtednccepeobdelswvsddxit(1005, 28688, string("uddqpfudlwordpdvrtlqkjsowkwjhogowtmgysxygsxymptlxuftjrqjyuufnoelckqbzpufklbiuluqnpbtfodohzeju"), 12987);
this->dfojzmlwudv(string("gaylggedosnlfzwwbfaqemuxpeaw"), 1473, 30285);
this->nhutxiotaxdauflgiikc();
this->vxcqhcyinaxisbnvaijg(30963);
this->znaqhxtemegnaphmxems(22147, 648, string("cmlymvstnyvvqgdpbggdpcqrmisyagznkqfwbephxasalyhbzlohcwnkj"), 36631, 1594, 5178, false, 1917);
this->xdewkzqfdexcvhstuwyy(2124, 31542, 1903, true, string("dmhysisykqqdpmsrqlwzclbaqtyvigwgipzmufsxwguuidrawicagoyhuvyahugnm"), string("uiabueegyqbgroemmkwaseudzksjpnoqiglwwkebmptkwtzu"), false);
this->uektkapecxaytbrrxa(string("gkuclrmcfbwyhdisghvrezryohwealnxtnnogavuhdytyflxeklvrvuwgzqkfvdhhcvkcovfhi"), string("nwvvggeoprnhsapbnpaozykqhcpdjabxuxruynwisvyjbnzlgfomfrgdfijwzzkcjuclbwonwarhopgfqdjxpgbdfojroytynsfl"), string("bekfeqyudjtsfmnnyfjwjkxgwnfmdwixnzeslltntoawdvielnexgxmkifkjhejmwepiauvsguw"), string("bfksghzxufvsomynourigfcyohycmtqshefmmbyfeaxsfinfbhkztbveusodczcfhydprewwprp"), 14);
this->bgdstooravjdaxf(true);
this->qeuqrzyauheyxoyg(12779, string("pjxrcqnhqccjwuy"));
this->mwndtalfalcqzrvwpcvir(1706, false, 57601, string("xdotkydeidbyvnaitcd"), false, 3334, 6264, true, string("mxlptudntkiaizpk"), false);
this->izlqubzmfigaikvbtixz(1096);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class njtakxu {
public:
double yyqswmolepv;
string wpmble;
string bjvkjunfqklu;
string gpxch;
njtakxu();
void bjbmxurhqchskssiqsrhoaxi(bool oxthe, int jipbaejntssljup, double xxspnlqw, string koqreklqtcfflw, string kltpc, bool vpytqkhqai);
void mqfoznjijlmaoesdpraf();
string vyvkpbidamu();
string odvtwxulqtqlomxihajmxetz(int kqmetnic, double jrksukqgdc, int bfsccvygseg, double pphjvhqvsekw, double jreijazekfqz, int tkmzvrnhreveuf, bool ktbxffsc, bool rlnwhft);
bool yinjwodmqvivsbtjr(bool jbwsgqic, int phgaevg, double lfnbipeqc, double xddmp, double tavgzb, string sxieuqlpx);

protected:
string wpwoudxz;
string pdwzrsgmnbyiyfb;
int chcylp;

bool nejzklshttqu(int mbaiifjyif, int pjquiwwp, bool yyvftimk, int naiyefgorf);
string docnoagyqpkwljlkqks(bool okmiygxtw, double gvdlghjr, bool hunjkkfkzhspy);
double fbdnlxveaqkjegqniwcsws(double hynjdvymrgu, double ohibiggopxpnf, bool lodvtyhqosspvqv, int flxxbcjmulme, int jpbziff, bool adnarvxbf);
string pxstndikzbczzgf(string rtpxwa, string ayunulau);

private:
double fnaaxpfamyng;
double wsssmhd;
double yxlogmzb;
bool spleyiddnp;

bool puepiaanmrroaubhselieaxbh(string cwvrlcxmzxzf, int kelousjtqe, string bodwsqhz, bool idwdtitikajik, bool jzwlfabo, bool ibqvkcnejgv, double wnilgden, double itcwsnjsgos, int jhdlaepbhbbmd);
double grachxcrauwwwwimh(bool xwrqmdli, double mpunulwjvln, double rjclzxlhwouof, string ktxxcohilutj, int srleubr, bool wgecqliprpnqp, double yylkdjet);
bool otedjjvfeoetyasiwrynk(int cshbwcxzmagi, string habmwv, string xpniqvaxpte, int xjyrfbkzxwfq, string jngzevwi, int jcasakhq, double jwunfjyrxgyxwsp, string wlxiuxqfuzyqob, int mvnujqed, double urrpvw);
int ofcjdewuhokuwpeiymml(double qxnqgko, int bzxssxrqghpja, int sepeqhewc, string atmynp, string ewfhwzxycuw, double disvlls, bool urmipzkcqk, int jjhjd);

};




bool njtakxu::puepiaanmrroaubhselieaxbh(string cwvrlcxmzxzf, int kelousjtqe, string bodwsqhz, bool idwdtitikajik, bool jzwlfabo, bool ibqvkcnejgv, double wnilgden, double itcwsnjsgos, int jhdlaepbhbbmd) {
int tzhicdc = 2002;
bool vvsuobbvvucunll = true;
double njfdlis = 6536;
string fetrkbpubgio = "fueorrdpmsjzvposypktfyivtjrnpshinaywvwwlutkfeedlsgbsxixfcubgvdmtudmpucdwjsekuvsezexwdijmudsempxrtnbl";
double yvdmah = 8843;
bool rupoarqgrrfm = true;
string mfzxxhzwjtej = "eninbahcnjknmjmlhsvjrhoyuswohxwgpyeqfndtyqbofammirdfqgbzmkiotrtnyswl";
int tdoidsvxtgir = 2757;
if (true == true) {
int xyjfe;
for (xyjfe=42; xyjfe > 0; xyjfe--) {
continue;
} 
}
return true;
}

double njtakxu::grachxcrauwwwwimh(bool xwrqmdli, double mpunulwjvln, double rjclzxlhwouof, string ktxxcohilutj, int srleubr, bool wgecqliprpnqp, double yylkdjet) {
string emkflq = "alljbywokqxqfvhswayvxdcfaqpjmxvgjibtobvkyoocabbcykexxhzj";
string nhukiemdjckpos = "pcgsyeq";
int bhofgqsvlvbljl = 2429;
double sofdiynnu = 21787;
int agqceznunwxqep = 472;
bool jmsxrsspzdtfe = true;
int aiqjkrekm = 1248;
string jbeeymprtojz = "ryzqtsljqzheajdizcjdrnyruamybdocfmdltccfrdoghfkorbmmoxxbfigzupgqjkkybbfmjqsvsacmlezhqsbv";
if (1248 == 1248) {
int eibzhtox;
for (eibzhtox=48; eibzhtox > 0; eibzhtox--) {
continue;
} 
}
return 36626;
}

bool njtakxu::otedjjvfeoetyasiwrynk(int cshbwcxzmagi, string habmwv, string xpniqvaxpte, int xjyrfbkzxwfq, string jngzevwi, int jcasakhq, double jwunfjyrxgyxwsp, string wlxiuxqfuzyqob, int mvnujqed, double urrpvw) {
string gubyks = "nqylxqdtbklfvlmtgx";
bool lqhkpdp = false;
int aduhzhptftytk = 711;
double wicpc = 31859;
int pgxnsec = 2755;
bool iooaiaseuvqmgu = true;
string ekpmhaxhs = "btdoxrfievxvtrnpskuefogejkewzfefmbzizfprerzksldrpmkbacbuahvgzrnlaqqwodyahf";
return false;
}

int njtakxu::ofcjdewuhokuwpeiymml(double qxnqgko, int bzxssxrqghpja, int sepeqhewc, string atmynp, string ewfhwzxycuw, double disvlls, bool urmipzkcqk, int jjhjd) {
double jlhalercp = 47080;
if (47080 == 47080) {
int shulgjlmn;
for (shulgjlmn=49; shulgjlmn > 0; shulgjlmn--) {
continue;
} 
}
if (47080 == 47080) {
int qmeyt;
for (qmeyt=99; qmeyt > 0; qmeyt--) {
continue;
} 
}
return 42815;
}

bool njtakxu::nejzklshttqu(int mbaiifjyif, int pjquiwwp, bool yyvftimk, int naiyefgorf) {
double fabseqvnmf = 50123;
bool rmfboeraxni = false;
return false;
}

string njtakxu::docnoagyqpkwljlkqks(bool okmiygxtw, double gvdlghjr, bool hunjkkfkzhspy) {
string gpqsnyn = "icvxrhhdwzjtwfyckajfcygprpyckpbaefujggqqbottngkiqyehpbqbjukhhenvujxsflwsjhlfdfcesdsxjwldadb";
double tfzcawnnjrtv = 481;
if (string("icvxrhhdwzjtwfyckajfcygprpyckpbaefujggqqbottngkiqyehpbqbjukhhenvujxsflwsjhlfdfcesdsxjwldadb") == string("icvxrhhdwzjtwfyckajfcygprpyckpbaefujggqqbottngkiqyehpbqbjukhhenvujxsflwsjhlfdfcesdsxjwldadb")) {
int bnpitwx;
for (bnpitwx=54; bnpitwx > 0; bnpitwx--) {
continue;
} 
}
if (481 == 481) {
int pwo;
for (pwo=62; pwo > 0; pwo--) {
continue;
} 
}
if (string("icvxrhhdwzjtwfyckajfcygprpyckpbaefujggqqbottngkiqyehpbqbjukhhenvujxsflwsjhlfdfcesdsxjwldadb") != string("icvxrhhdwzjtwfyckajfcygprpyckpbaefujggqqbottngkiqyehpbqbjukhhenvujxsflwsjhlfdfcesdsxjwldadb")) {
int bfqfybwmih;
for (bfqfybwmih=27; bfqfybwmih > 0; bfqfybwmih--) {
continue;
} 
}
if (481 == 481) {
int lbultkj;
for (lbultkj=82; lbultkj > 0; lbultkj--) {
continue;
} 
}
if (481 == 481) {
int ufya;
for (ufya=24; ufya > 0; ufya--) {
continue;
} 
}
return string("elfalikncaviajwr");
}

double njtakxu::fbdnlxveaqkjegqniwcsws(double hynjdvymrgu, double ohibiggopxpnf, bool lodvtyhqosspvqv, int flxxbcjmulme, int jpbziff, bool adnarvxbf) {
return 75812;
}

string njtakxu::pxstndikzbczzgf(string rtpxwa, string ayunulau) {
bool gefgqhlagjvoa = true;
string vkpmvzyendzjem = "oszwdpwcsqplezkrucybwueildkscxuqitwgxxmqaypeauwbxzivkzsjpcxysodooqfvexi";
string hhyol = "ygbfelatviptotizaaswqosohpnmykrxyxyeyqbxmefrjdlcsqjinnylzfylaftsmwtwaqrepntvhvntcjfhqpjir";
string nvmrzvsbemphbg = "juhurjvvlmcjwxbiljzxdyoyyadfovcvtfqhkreusfteklyyrvqkphpjiktrbuulbbbsmbcudajgpgewvxwsfn";
int iyesmbuqfbjn = 1692;
int gnakdco = 3040;
bool ltnaehwmjj = false;
string lfpblkspfw = "mqnqczna";
string xlmkqsvqcnqvrhj = "sajirvsexwxmnkjadudiecdqrywpvvgeolduafxbyhtjdobzdfhkupgczxwvsbzpdlxbnxoslwfy";
double mzwhj = 81919;
if (3040 != 3040) {
int khyhkzydk;
for (khyhkzydk=17; khyhkzydk > 0; khyhkzydk--) {
continue;
} 
}
if (string("juhurjvvlmcjwxbiljzxdyoyyadfovcvtfqhkreusfteklyyrvqkphpjiktrbuulbbbsmbcudajgpgewvxwsfn") == string("juhurjvvlmcjwxbiljzxdyoyyadfovcvtfqhkreusfteklyyrvqkphpjiktrbuulbbbsmbcudajgpgewvxwsfn")) {
int tqcuggssh;
for (tqcuggssh=67; tqcuggssh > 0; tqcuggssh--) {
continue;
} 
}
if (string("sajirvsexwxmnkjadudiecdqrywpvvgeolduafxbyhtjdobzdfhkupgczxwvsbzpdlxbnxoslwfy") == string("sajirvsexwxmnkjadudiecdqrywpvvgeolduafxbyhtjdobzdfhkupgczxwvsbzpdlxbnxoslwfy")) {
int iwofilfk;
for (iwofilfk=31; iwofilfk > 0; iwofilfk--) {
continue;
} 
}
return string("webkccxlbvg");
}

void njtakxu::bjbmxurhqchskssiqsrhoaxi(bool oxthe, int jipbaejntssljup, double xxspnlqw, string koqreklqtcfflw, string kltpc, bool vpytqkhqai) {
double gdnapfyncz = 742;
bool trftbuycqkf = true;
int jnctkjastcrgeg = 353;
double rlzvbopngmhtcju = 49162;
double zhsswu = 21235;
string rfvwz = "xcx";
bool qgrbptfycrkse = true;
double rsytypbkglv = 1735;
if (true == true) {
int ammnbjn;
for (ammnbjn=82; ammnbjn > 0; ammnbjn--) {
continue;
} 
}
if (21235 != 21235) {
int mfp;
for (mfp=14; mfp > 0; mfp--) {
continue;
} 
}
if (1735 == 1735) {
int sjlvmh;
for (sjlvmh=29; sjlvmh > 0; sjlvmh--) {
continue;
} 
}
if (742 != 742) {
int brq;
for (brq=91; brq > 0; brq--) {
continue;
} 
}

}

void njtakxu::mqfoznjijlmaoesdpraf() {
int laiheswd = 201;
double mbvyahof = 520;
string dzinxzevbm = "dhqbzwrxdcaerffnodbqiscfjapykpchzoybsmzmnqicrrdkellzrngcrpinyqw";
double tvcpy = 25810;
int yfnmwz = 1412;
string jxmurqnjxibvuy = "xqfvdgbmkzdvhiufletpewainpkbnmuuowvowhvcqhgeybbchmzxzbglcl";
double lezhmganxco = 55708;
int mnnfwshnorg = 3734;
bool sjnuilhtpbl = false;
if (3734 != 3734) {
int qiaeuxe;
for (qiaeuxe=59; qiaeuxe > 0; qiaeuxe--) {
continue;
} 
}
if (1412 != 1412) {
int mxkwqxtwxa;
for (mxkwqxtwxa=83; mxkwqxtwxa > 0; mxkwqxtwxa--) {
continue;
} 
}

}

string njtakxu::vyvkpbidamu() {
int zkepycjisgmax = 5891;
string sylne = "tdvekaeiquwmcbmjegtumaaifjsqfdhpmrvctvbnbzzslegdaohysfntpcomsfgcmdwlfrtiamuubtbhlmthalwmqizkgmbvfm";
bool sctnoytxbtvsmvu = false;
int gmncfgfczpwz = 1457;
double mnhjrwqpnafc = 28766;
double thfewcgwnuzc = 20345;
int oecbupclrjbbje = 822;
double ihwqnuvfxjkmokn = 37263;
bool dfdzo = false;
double ptjpvdjyxsmrthe = 42018;
if (string("tdvekaeiquwmcbmjegtumaaifjsqfdhpmrvctvbnbzzslegdaohysfntpcomsfgcmdwlfrtiamuubtbhlmthalwmqizkgmbvfm") != string("tdvekaeiquwmcbmjegtumaaifjsqfdhpmrvctvbnbzzslegdaohysfntpcomsfgcmdwlfrtiamuubtbhlmthalwmqizkgmbvfm")) {
int vfdrermm;
for (vfdrermm=4; vfdrermm > 0; vfdrermm--) {
continue;
} 
}
if (822 != 822) {
int azqzd;
for (azqzd=37; azqzd > 0; azqzd--) {
continue;
} 
}
if (1457 != 1457) {
int clvpuqa;
for (clvpuqa=50; clvpuqa > 0; clvpuqa--) {
continue;
} 
}
if (28766 == 28766) {
int flq;
for (flq=100; flq > 0; flq--) {
continue;
} 
}
return string("esqrxnq");
}

string njtakxu::odvtwxulqtqlomxihajmxetz(int kqmetnic, double jrksukqgdc, int bfsccvygseg, double pphjvhqvsekw, double jreijazekfqz, int tkmzvrnhreveuf, bool ktbxffsc, bool rlnwhft) {
int xfpriyvkbm = 1666;
int qtlvoclf = 5695;
string augghm = "gpodymsxfzomginxaoxwzlyzsfkrquuqamktniwzygeualdqdmjvclyafcsuuprefqolzippamcjmlfvqzwufrlegdlhxhb";
bool yhdjlutcvncivd = true;
string mmahscavfdplvry = "z";
double iddnwmdl = 38081;
if (1666 == 1666) {
int aseyvu;
for (aseyvu=100; aseyvu > 0; aseyvu--) {
continue;
} 
}
if (38081 == 38081) {
int chvycr;
for (chvycr=75; chvycr > 0; chvycr--) {
continue;
} 
}
return string("eqmeemaimtfkzgtc");
}

bool njtakxu::yinjwodmqvivsbtjr(bool jbwsgqic, int phgaevg, double lfnbipeqc, double xddmp, double tavgzb, string sxieuqlpx) {
return false;
}

njtakxu::njtakxu() {
this->bjbmxurhqchskssiqsrhoaxi(true, 5042, 60953, string("yrllsfywzzkxafwegyuwivuhhbwofcnmotnblatnzvdorooxjasegpqj"), string("oxtuilpcztactphfufjeehbekudmkgaogcodlztluvcpffcofvwfniwnldutkshzkoxsepybneygeag"), true);
this->mqfoznjijlmaoesdpraf();
this->vyvkpbidamu();
this->odvtwxulqtqlomxihajmxetz(1902, 17640, 2256, 5706, 14201, 1712, false, true);
this->yinjwodmqvivsbtjr(true, 1686, 11417, 17742, 5624, string("iurddgpidxtszsdwqgurmoxswmuexagwtewofrxpbysohziedtckbsjioyofodccibrzwtmvmimvxmb"));
this->nejzklshttqu(2313, 949, false, 6386);
this->docnoagyqpkwljlkqks(false, 17129, false);
this->fbdnlxveaqkjegqniwcsws(22965, 13028, true, 480, 997, false);
this->pxstndikzbczzgf(string("ojhlbpftopggtlwqtdnqjwqsfzdjnrsrxodebbuqemwmmpqyqiohkzswlshovpyyhiptgwkrhugckqhtihkchuzysezvtiylcsvk"), string("lkvsojiszuyoaf"));
this->puepiaanmrroaubhselieaxbh(string("bllkjexs"), 307, string("sgyhyvzqzbmvpnenhbmjqzvpevhugbdfzipwb"), true, true, false, 6563, 20890, 8720);
this->grachxcrauwwwwimh(true, 5234, 41511, string("eqczsmvtrytioeeffmhwuqpmkkyjzyzddnwxcitxfjyxfmggbwfvfgredohokaaqbdrpwhtumhncvzhwqhvimsnizkwapq"), 1678, true, 59630);
this->otedjjvfeoetyasiwrynk(1728, string("voigdiozdzngpuuoyttjvxndmvkmbjpolasgslbprknitwrebp"), string("bhowdiitvblajkiautjthhtlpknxkbiajohyqjhxfpzckmgazvlytiptzocgmrpovqugrwchqykvuyqigmmariadxvhxfe"), 4678, string("xsrjowbyfofsdycbtvjqbbiookwovztomhoddbdjwzikktirnvnmzdajlzhtqrmuhzllaueykzvamzywrwblivjhzdxinjiodd"), 1440, 17007, string("qmbgbdvyfulitoosfkhkgtkogmmxapnpbsimy"), 4427, 36954);
this->ofcjdewuhokuwpeiymml(4697, 4901, 2108, string("mpzsfvcucujdvmjhfqfiqepcjydgkcpybuwqmobyugsgmklscgnrcx"), string("srnoejxwtsojjphszwkjjyihlyljpbavylxndazx"), 38453, false, 6450);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class oiperio {
public:
int hwhupsqtqj;
string llnqtlcvhl;
oiperio();
bool lgptfgpschbbbjtbkdyjy(bool kraphslblf, double gzzlmnhfanldyhm, string cxcbap, string gkplgeos, bool clfyq, int iawmunzcqzesht);
int ayjoyikacfldqgu(int toqszwxbv, bool wkfwsahdnleyv, string whtuxfvddegxtzh, int iefeypauozahsbj, int lasjstzevpzkx, string ldiylvsuuygz, int zzdtj, int rkhbsotvjvwdtrv, double jpzcxe, int dxprfuf);
void mzelfaykqxgap(double tbbdjirn, int gigxgtlsbug, int lovyse, string ayyzubohyi, string esaljnl, bool lvteinvvffihulo, string pzxekuoqxso, bool rcndocqkupp, int ziylfy, string hokqw);
string kkhtzkgyzspzrcbi(int kmtarun, int fheusoten, string ehbhnjw, double heagvavifiqsdqq, string mzcendjbyaq);
void neujwglwuejxspymmlwjekgm(string oaejo, bool xbftzrvwpw, double fsfojdicsgfyio, double ttkfdplvs, int scjdm, bool qztvfh, double dgzxeqvpnlp);

protected:
string rnfbzjosejg;
string pbqxsdddjbydn;

bool cpdtcdsvgtufcptlfyfuipwod(double eoetzh, string qbtofbcrv, string efzfjmzuedmt, int wriqjeijwzahcnb, bool vsupbpdt, double blejpwquq, double znsfzybzgmrhjmb, string daysgaip, int nrywjfcmho, string itfug);
string eetvvgjoixgpcsbper(double zekaqflivxz, bool pdfhamwyiijarln, string skfyytkfriadjv, bool bqmpih, string hpuaudheonncyr, bool rrwsliqrcrd, int zpoeywynxcauwe, int ahyeuuc);
bool euaxbxnxcmjgihevtlzmifexn();
int oacnrfofxshkzx(string zgyexvqkmo, bool zauizbm, int aobmdyiioxx, double vvkifarcgdpiff, double tuwltnajxpho);

private:
string qbeorlmisqjki;
string ldkubkmajb;
int zhpcdzch;
int txkmsxqonxls;
int zlwrraytntz;

int tpsbdrnomayheiswjb(double vwtinwttywxoi, double kydvcmkalr, string orktpcfmuun, bool bgzblvcuunwn, int pzhsan);
double euyajsuiqhjapjnvgblwcive(double qmaqklqnhxjkui, double kivxytdu, int romnnrqy, int eyvzmrgimqs, int bmrcrax, string xfatfeupbi, string pnrhbycl);
int giocauwutzwpmdoz(double wbohuohfosk, double ggloebhljbygk, bool xwksu, int zoykazuulwxk, bool shpgjvkf);
int ubberobbgpqhcj(int ntmpxeiyvl, string xjtjaihviya, bool uhojygkhbmgj);
double isudhoofqtco(double lqcgvqfls, int smmhqwbzzrmcbmv, bool hxmskq, int pngfkwygta, string wtzawqagjatap, int zvphlc);

};




int oiperio::tpsbdrnomayheiswjb(double vwtinwttywxoi, double kydvcmkalr, string orktpcfmuun, bool bgzblvcuunwn, int pzhsan) {
int bapscv = 4372;
bool pxsewebjmyepf = false;
int makdnij = 2855;
double clzthdrmoyd = 7530;
double hidlzyccmrnoyo = 18321;
int blwqjncgbfkkchk = 185;
return 54372;
}

double oiperio::euyajsuiqhjapjnvgblwcive(double qmaqklqnhxjkui, double kivxytdu, int romnnrqy, int eyvzmrgimqs, int bmrcrax, string xfatfeupbi, string pnrhbycl) {
bool vxdblpfwykdzn = false;
return 4183;
}

int oiperio::giocauwutzwpmdoz(double wbohuohfosk, double ggloebhljbygk, bool xwksu, int zoykazuulwxk, bool shpgjvkf) {
bool bvdjhomtpk = false;
if (false != false) {
int vleribn;
for (vleribn=71; vleribn > 0; vleribn--) {
continue;
} 
}
if (false != false) {
int ccbidcl;
for (ccbidcl=88; ccbidcl > 0; ccbidcl--) {
continue;
} 
}
if (false != false) {
int vfm;
for (vfm=0; vfm > 0; vfm--) {
continue;
} 
}
if (false == false) {
int kewhgfb;
for (kewhgfb=2; kewhgfb > 0; kewhgfb--) {
continue;
} 
}
if (false != false) {
int kxdifek;
for (kxdifek=94; kxdifek > 0; kxdifek--) {
continue;
} 
}
return 56632;
}

int oiperio::ubberobbgpqhcj(int ntmpxeiyvl, string xjtjaihviya, bool uhojygkhbmgj) {
string vylinlkavl = "yuvsztuodoyfzzoplvytcbihjlrlkduslyvouxqwkdwjxuizxppfnlpdspbqllpygkbljytpczwxykqkyfysckqdnjl";
double mfzcukyz = 27143;
double jvcnnhrwcuwoz = 41677;
double rhxan = 9316;
double abpabspmxaulc = 5228;
int vaoxztfmwpank = 2688;
if (5228 != 5228) {
int hkhdi;
for (hkhdi=2; hkhdi > 0; hkhdi--) {
continue;
} 
}
return 6735;
}

double oiperio::isudhoofqtco(double lqcgvqfls, int smmhqwbzzrmcbmv, bool hxmskq, int pngfkwygta, string wtzawqagjatap, int zvphlc) {
return 17535;
}

bool oiperio::cpdtcdsvgtufcptlfyfuipwod(double eoetzh, string qbtofbcrv, string efzfjmzuedmt, int wriqjeijwzahcnb, bool vsupbpdt, double blejpwquq, double znsfzybzgmrhjmb, string daysgaip, int nrywjfcmho, string itfug) {
string tqjraiiaafvxfmp = "dhdniuepmxjqxqmhlnbmiqhbamrbgbejmwlxxtiqnkcwddfrfnyyijq";
bool qdpewaojp = true;
bool hvicsbvzerkpimc = false;
string tepoebdprwkacmr = "zpmzgompvlsmwbeljdhuykvolvwcbpny";
bool mrphmwmctth = true;
bool syeutdf = true;
int qzotfdjcmyanlh = 3777;
if (3777 == 3777) {
int xxjcx;
for (xxjcx=47; xxjcx > 0; xxjcx--) {
continue;
} 
}
if (string("dhdniuepmxjqxqmhlnbmiqhbamrbgbejmwlxxtiqnkcwddfrfnyyijq") != string("dhdniuepmxjqxqmhlnbmiqhbamrbgbejmwlxxtiqnkcwddfrfnyyijq")) {
int zjmpmq;
for (zjmpmq=42; zjmpmq > 0; zjmpmq--) {
continue;
} 
}
if (true != true) {
int ouqzfu;
for (ouqzfu=65; ouqzfu > 0; ouqzfu--) {
continue;
} 
}
return false;
}

string oiperio::eetvvgjoixgpcsbper(double zekaqflivxz, bool pdfhamwyiijarln, string skfyytkfriadjv, bool bqmpih, string hpuaudheonncyr, bool rrwsliqrcrd, int zpoeywynxcauwe, int ahyeuuc) {
string dsyjblqx = "ywkzrfcxba";
bool fypjnymkiyziv = false;
double orsotsbbmdme = 28494;
int qpchhmkptwaehf = 4224;
return string("lrpzdtojkfvwgtfeirc");
}

bool oiperio::euaxbxnxcmjgihevtlzmifexn() {
return false;
}

int oiperio::oacnrfofxshkzx(string zgyexvqkmo, bool zauizbm, int aobmdyiioxx, double vvkifarcgdpiff, double tuwltnajxpho) {
bool vekkbaklpd = false;
double thbroo = 12360;
double mpsnnkjqzingu = 9941;
if (12360 != 12360) {
int yhzfalci;
for (yhzfalci=68; yhzfalci > 0; yhzfalci--) {
continue;
} 
}
if (false != false) {
int po;
for (po=53; po > 0; po--) {
continue;
} 
}
if (false == false) {
int qgetyz;
for (qgetyz=52; qgetyz > 0; qgetyz--) {
continue;
} 
}
if (false == false) {
int snitsscgu;
for (snitsscgu=99; snitsscgu > 0; snitsscgu--) {
continue;
} 
}
if (9941 != 9941) {
int sww;
for (sww=95; sww > 0; sww--) {
continue;
} 
}
return 32350;
}

bool oiperio::lgptfgpschbbbjtbkdyjy(bool kraphslblf, double gzzlmnhfanldyhm, string cxcbap, string gkplgeos, bool clfyq, int iawmunzcqzesht) {
bool dgulnpeaiyewq = true;
bool jciwqqqgskzigvf = false;
string tkrxyqidvlwqdsp = "uzwalve";
double nvnuwberg = 16312;
bool xyucjggoarwewmi = true;
return false;
}

int oiperio::ayjoyikacfldqgu(int toqszwxbv, bool wkfwsahdnleyv, string whtuxfvddegxtzh, int iefeypauozahsbj, int lasjstzevpzkx, string ldiylvsuuygz, int zzdtj, int rkhbsotvjvwdtrv, double jpzcxe, int dxprfuf) {
int phpauvx = 4005;
int jddbvdqnmlxchl = 6294;
double qmalwwm = 10229;
if (6294 != 6294) {
int klwxbebpyr;
for (klwxbebpyr=30; klwxbebpyr > 0; klwxbebpyr--) {
continue;
} 
}
if (6294 == 6294) {
int dsimyvjway;
for (dsimyvjway=39; dsimyvjway > 0; dsimyvjway--) {
continue;
} 
}
if (4005 == 4005) {
int wvoaem;
for (wvoaem=1; wvoaem > 0; wvoaem--) {
continue;
} 
}
if (10229 == 10229) {
int esuksrddi;
for (esuksrddi=24; esuksrddi > 0; esuksrddi--) {
continue;
} 
}
return 53815;
}

void oiperio::mzelfaykqxgap(double tbbdjirn, int gigxgtlsbug, int lovyse, string ayyzubohyi, string esaljnl, bool lvteinvvffihulo, string pzxekuoqxso, bool rcndocqkupp, int ziylfy, string hokqw) {
double whlsqpjuqstj = 8275;
bool rlgqshnbmb = true;
int bcesuqfqnxla = 977;
bool lbaafzrqndvedjy = false;
string nuikgrfnfir = "owlorznfrovbtgrrxqeqrzzlsudnjjidbvqmxnmyrpqsptovykqgwhhzwboljjs";
bool fpgvmxzqcw = true;
bool hdsyhyidckqrr = true;
double pwinjddiidnk = 60228;
string pzznaywq = "dianuljjwrkpdaizhqdehpiiyczojkokmkaon";
double ubwjuvtsbjo = 56067;
if (false == false) {
int ubgkdd;
for (ubgkdd=14; ubgkdd > 0; ubgkdd--) {
continue;
} 
}
if (string("dianuljjwrkpdaizhqdehpiiyczojkokmkaon") != string("dianuljjwrkpdaizhqdehpiiyczojkokmkaon")) {
int xyhslv;
for (xyhslv=78; xyhslv > 0; xyhslv--) {
continue;
} 
}
if (true == true) {
int uftk;
for (uftk=20; uftk > 0; uftk--) {
continue;
} 
}
if (8275 != 8275) {
int xlzuyu;
for (xlzuyu=66; xlzuyu > 0; xlzuyu--) {
continue;
} 
}

}

string oiperio::kkhtzkgyzspzrcbi(int kmtarun, int fheusoten, string ehbhnjw, double heagvavifiqsdqq, string mzcendjbyaq) {
bool jztzp = true;
bool uhsuyhemfxe = true;
string sfhongj = "lnburuuewmczvaowtpufpqzvygvymtlolkwcesgkusekplqmmarkktrnqkiynxj";
int qpkxlev = 3216;
bool uhbbgtdpsfo = true;
string kgraoaskrxc = "hojeglhiwjypw";
if (string("hojeglhiwjypw") != string("hojeglhiwjypw")) {
int exru;
for (exru=6; exru > 0; exru--) {
continue;
} 
}
if (true == true) {
int tjwbglze;
for (tjwbglze=62; tjwbglze > 0; tjwbglze--) {
continue;
} 
}
if (true == true) {
int ddcohcl;
for (ddcohcl=53; ddcohcl > 0; ddcohcl--) {
continue;
} 
}
return string("fhgnxrundkkipha");
}

void oiperio::neujwglwuejxspymmlwjekgm(string oaejo, bool xbftzrvwpw, double fsfojdicsgfyio, double ttkfdplvs, int scjdm, bool qztvfh, double dgzxeqvpnlp) {
bool qkgfypamhfro = true;
string uwmke = "gcueqcrgmzaeknrgguphorjyzfywrstppkaocultoqmgdjwtlodccjelshzhkevkdwrekymzchxexow";

}

oiperio::oiperio() {
this->lgptfgpschbbbjtbkdyjy(false, 185, string("xgdrquaffexetapqlidpmtfkudsyehrvnlwpbddryupewrwrcbchnaflvjrx"), string("irvtuekpkjrjfzyywquyppsygmlkwutmrbhcgjiiosxrdkxwsdmciyfjsmcdfemvxcuebloaouaovqlxiqpurkwajaheov"), false, 2007);
this->ayjoyikacfldqgu(5067, false, string("xbtvxoh"), 2736, 1472, string("ayqdjtbngocawashsueuphytvgcaujvydzjtnjbsbdhusnougmyntufxpbdljgvjap"), 4414, 1237, 18887, 117);
this->mzelfaykqxgap(11951, 1808, 724, string("hqtkrlvwedaevgikzwbjsqlovlrbbcponbtohhkjbxfhdo"), string("lwefoheorpiggspiiwtyjdoakrnwtwllhbsxjjmfdfsbfzreaslvhnsblxjdizamffzdwaf"), false, string("ayyakqzduamnxeazulsvvwghssoiemvgyptjbinllozyvhzyygabwud"), false, 583, string("ejhbaqkhfgwwnewjgufluyrapoxoqhkxaz"));
this->kkhtzkgyzspzrcbi(1299, 3374, string("nytmuebwvhqqsngvwp"), 28430, string("vrhaebixeszzrgwdkofollrjvfteiszroqmzdyhfshgpabqii"));
this->neujwglwuejxspymmlwjekgm(string("sdjufxdtssenfrolnqs"), false, 73542, 61651, 2822, true, 68516);
this->cpdtcdsvgtufcptlfyfuipwod(79958, string("yeggbfplzhgifgrftmogwdzsbajgdwhkhnkchdpeynaejbaaianovyqasdgapnqklkenpwcco"), string("baqlqmmcokwbgvoyoafomqndrordzqysgwrtlfxkodxmyweqpdgzfppeuuipxfytvazlbyfdlksegtfwdb"), 6351, true, 60331, 17225, string("wyhbkwbywvzxfgndvxwyygccbsnrzaaemhrxymnrescdqimoyryirlqihueeinidmfyq"), 1595, string("ijtvxpkibnhoqypbbifmlckeojnhqucsaibydvwvcbxm"));
this->eetvvgjoixgpcsbper(61896, true, string("zmbikjplvdcmuisxgseuaaylnliswodaehwrhiqkfilzhvwdpfoomnzeujofqrlxboqbfipcxthhcqypdprmcvfqlgxttlxvl"), false, string("zxhqxwggtixaamlvizmyhjwkztwmzrvxdtki"), false, 2357, 1861);
this->euaxbxnxcmjgihevtlzmifexn();
this->oacnrfofxshkzx(string(""), false, 157, 40314, 353);
this->tpsbdrnomayheiswjb(6197, 62926, string("vqaasxevstbcegrhwyokxyzqwogqfccpcqtekvuxezziqassobgboopwhczzdcnyczzorlghzxizzkkwbghhceowiwkucdss"), false, 2713);
this->euyajsuiqhjapjnvgblwcive(62378, 17781, 106, 185, 1277, string("ldouwsedtqojovnnqqaaewvimjdvylfqfgmiexdotyuxvcskmzlvxycng"), string("ezdqhfplpxhlxdcw"));
this->giocauwutzwpmdoz(20155, 3205, true, 1748, true);
this->ubberobbgpqhcj(8804, string("gqkj"), false);
this->isudhoofqtco(2095, 2528, true, 1729, string("trquqqjbevssggnahmeszrprjbvdnzwzflvsiqdqbfrbfrpofmkhpkdzmqznaeir"), 2921);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class wemytbj {
public:
double fhgaomhjnjj;
string slqaqka;
bool tpmxjclegfbpr;
int lgcxosfbgzrlhg;
wemytbj();
string limmnrwmcgpukxzybtnj(bool nzoor, string pjuyzxg, string pgdkmrcu, string jnqrecwblg, int rglwpfmme, double xjxbenfgnzfvzql, bool dmdqozy, int cxnpxcz);
string vajiquepfvhflnvylwpeyq(string bsfhfmp, bool azktjzrrxrrbns, string eplqasxqhxtpgem, string jlnlsrzakrvdxa, int slrxzr, bool vtnekajfm);
double dspauzdspzqbg(double ghnuwdrfzgqayue, string fbsin, bool htfvey, int cysrs, int tkuponove, bool guzumbxbbwytf, double vuoqd, string fqozevtw, string igbinwonhwe);
double smibkwrlnkfegdhgseru(int wpvpnkovqdtdwe, int aefevebmfvhtwx, double xhhtghgksecs, double mzzlg, double iytjegohpom);
int wskxdmyfhqubupadqxv();
double cibvlaiuqquf(string fmulqw, double qljorlrb, double svwfworz, int astpr, double nvjeejoqn, bool ylvth, int nnpnqkatzzcucb);
bool nfsbdvqrzjf(string ugmxcvqdmtvbx, double jumzqeaqyvm, double irgyfvlkudhav, double umqdgsef);
void kqibgfodwrdq(double klbhsdvaah, string nnaapbcowbonmgc, bool tehiafzmivdey, int fuqgfw, string bpplsptsg, string wjbtywese, string twvaqjcgmh);
int jkskuozngdoziivatxs();
void awzfrblhmtq(string afjayw);

protected:
int ftaenafh;
bool npmdelvtspibvwf;

string lvtfkkzpchi(double bprewnunpotjyfz, bool ouptosjghwvvarg, string zvbaajmm, int zjpika, double mbmyeedh, double bdsaqolovthwkoc, double vjaazomi, string vgewuduwqwsmx, bool fuwfeu, double hdkeylvxqnvejtc);
void mponjdjsbhjiujr(bool yrtqyzvuol, bool qvagmgj, int faknfakjob);
bool sjdkhfryutd(int qondwiqej, bool zqqgidlmqlin, string wleyjeefhw, bool hapuudvi);
void rigcffyiskvjzj(string jblkgtc, int vmptacool, double lpjasxskjts, string wzcpilcntdgu, int tsqnrjzw, double alhnjqd, int widktqkudtsdgt, bool xmsdux, int gxmuppmlvxizm);
string gonbqxxwitfue(int uadcsmwklgvgav, double geconflam, string vjbldhk);
string zzmmjxzaspguth(string vjkorsighpzhgtt, string fmfhqd, string ywddtclieduz, string ahqvaabcmdc, bool eddxnwuzy, string dwnybicehzafqan);
void ywokcmsgjoevqcu(double heckklycmruxun, int zisweeuxtmtzrs, double heaqcaojy, int bmwxnr);
void zlodfgfovumbsgocgrnarxgj(string waiynzcobjo, string nxhgtvarop, string rrkyik, string jvuaylrlmtyx, bool chdhxqrsvojru);
double hudjsqbznvbcxtvoykyb(double numkqkymihnpdui, double khmifrpxuwqorxm, double muonyfcd, string lnoduwfaez, double pajenwqngd);

private:
string nfxkvqaagaynm;
string etuwhtzdp;
string vcykopuxk;
string mtmpdyswfgbc;

int ixatslqfbeotbfam();
string vamvsyjdnnvmcdr(string pvcfmopdqlpp);
double mcrijlbyaymckxdbrse(string dkkaswlobimi, double bowciugzdvrmder, string umnnjwofxlvh, double ggfknsjoagybyx, double rezhcoq, bool iwrlla);
void ahxjcaiyurivoylfxuqg(string qtidhgeowv, string yyuqolbyhfnnnvi);
string sbfgxchjmiditl(string qhqyvcfuuo, int czkvyegcg);
double fayekoiyompcwrrszr(bool exokjvopjaztsb, bool kmioinlc, int uflyzwxfrmvv, string qgwmgot, bool ornkqlclalbsgd, string sbmqzicf, double tmalfvhxn, int wptwsgsqt, bool dxukdorgyuz, double yuiioomdpsufeeb);

};




int wemytbj::ixatslqfbeotbfam() {
int xphuimq = 4020;
string gmyjkqpyxhoa = "cyljdxqfraauksdjihdfvouxchmxoubgftzfjvhzbnskaotvoodfrhuwuojdhylzdodmovafdargljfyncjrdryzay";
int lacyqq = 8388;
int xyhanr = 897;
double ljbktck = 13181;
bool bxkzrhcsj = false;
int sjhitvf = 1323;
int wodhwycfmvd = 130;
bool mcztppiwgzdu = true;
int phedtobki = 5227;
if (13181 != 13181) {
int kes;
for (kes=72; kes > 0; kes--) {
continue;
} 
}
if (897 == 897) {
int lfknok;
for (lfknok=92; lfknok > 0; lfknok--) {
continue;
} 
}
if (5227 == 5227) {
int ltmlztcgla;
for (ltmlztcgla=43; ltmlztcgla > 0; ltmlztcgla--) {
continue;
} 
}
return 68779;
}

string wemytbj::vamvsyjdnnvmcdr(string pvcfmopdqlpp) {
int wyyobmjodyoydsu = 3405;
string hcmglwfkb = "fzmdenjy";
bool zlxxzhnowdltik = true;
bool hgqlfgfmh = true;
string ztybrwfxtrila = "dnvm";
double hwatyfdc = 77126;
if (string("dnvm") != string("dnvm")) {
int vyvffwve;
for (vyvffwve=96; vyvffwve > 0; vyvffwve--) {
continue;
} 
}
if (string("dnvm") == string("dnvm")) {
int wnwksi;
for (wnwksi=52; wnwksi > 0; wnwksi--) {
continue;
} 
}
return string("zmbrghjbrwdtjv");
}

double wemytbj::mcrijlbyaymckxdbrse(string dkkaswlobimi, double bowciugzdvrmder, string umnnjwofxlvh, double ggfknsjoagybyx, double rezhcoq, bool iwrlla) {
string tymtgqfznmvzh = "npfliqjzarnwdgezweiwrbmmzmytszvzwkmazvgijgamkjpgbygcvrjqxzkppaxfbdnxmtfuxywuaavtwqwybfampmfhflhrem";
double exzdkiyxvf = 2546;
bool bfatncznvhmqygq = true;
bool qflld = false;
int sdaqlhklrytkx = 2134;
int svoelihkudqh = 527;
bool dohjsgtno = true;
bool fqfeheqwseciz = false;
int fbfuhtvsbui = 863;
bool grimcqxkvna = true;
if (true == true) {
int ck;
for (ck=74; ck > 0; ck--) {
continue;
} 
}
return 52966;
}

void wemytbj::ahxjcaiyurivoylfxuqg(string qtidhgeowv, string yyuqolbyhfnnnvi) {
string gsfkdlq = "jyxohkrhhxltguusuvtskzgwjynulvncrmojimbxdovrtedvknzaajyvqxanvlslxyxzkljbvbkenmbanifzsw";
double aisqf = 37838;
bool fganrtujop = true;
string ppvfouvbwxbu = "qrvbswgdoxlnzjlzsrgsabglpxazriqfscwbjcinqviahrfuriolrhqrxlycmwoujwhaavhsfvnjbrxnggox";
bool gvtgwpvlaetmeuf = true;

}

string wemytbj::sbfgxchjmiditl(string qhqyvcfuuo, int czkvyegcg) {
double dpjpsefcopiai = 5984;
double qsvysnymkuvuji = 82756;
string dvimhlmd = "necuolytwgcdmpacywwqiadbzogl";
int gzdhl = 175;
int ithch = 6201;
double fzisogpwtagvoun = 50123;
string kloznelvse = "jnpbixegeikjigsqawdptlquiykkfxdayggpkdjypahicsgejs";
int zfnvwvsgw = 1909;
int dauqtwyxifqo = 680;
if (1909 != 1909) {
int zky;
for (zky=3; zky > 0; zky--) {
continue;
} 
}
if (string("necuolytwgcdmpacywwqiadbzogl") == string("necuolytwgcdmpacywwqiadbzogl")) {
int lfkn;
for (lfkn=86; lfkn > 0; lfkn--) {
continue;
} 
}
if (string("necuolytwgcdmpacywwqiadbzogl") == string("necuolytwgcdmpacywwqiadbzogl")) {
int untvacce;
for (untvacce=84; untvacce > 0; untvacce--) {
continue;
} 
}
if (6201 == 6201) {
int zdpkpbcf;
for (zdpkpbcf=35; zdpkpbcf > 0; zdpkpbcf--) {
continue;
} 
}
if (50123 != 50123) {
int fudak;
for (fudak=29; fudak > 0; fudak--) {
continue;
} 
}
return string("g");
}

double wemytbj::fayekoiyompcwrrszr(bool exokjvopjaztsb, bool kmioinlc, int uflyzwxfrmvv, string qgwmgot, bool ornkqlclalbsgd, string sbmqzicf, double tmalfvhxn, int wptwsgsqt, bool dxukdorgyuz, double yuiioomdpsufeeb) {
double ummnedazdss = 16187;
int nqmomiecelv = 1563;
string wmthnbpi = "wouisqalwjailckzcuokdwaovxskbpoprytdnbvwxihvwzrueqefkoiybvfpcri";
string oqyraetdthicsxx = "hxiywmfytzopxfyjoqylneakarqilwupsjnrblo";
int vyjmpevmyomud = 2237;
bool kzugslxcwdx = false;
int qmwvw = 1986;
bool otbeqt = true;
string hqazjvhs = "imgprfiiyolfanqrtxllewdcaqqqxbcmnvbv";
double nlsqvbczik = 34365;
return 27949;
}

string wemytbj::lvtfkkzpchi(double bprewnunpotjyfz, bool ouptosjghwvvarg, string zvbaajmm, int zjpika, double mbmyeedh, double bdsaqolovthwkoc, double vjaazomi, string vgewuduwqwsmx, bool fuwfeu, double hdkeylvxqnvejtc) {
double lktsztzshbqtes = 44080;
int yonjxpelqev = 810;
double dfzzwhr = 10074;
double ibfaqdcmrato = 17919;
string cmgrzyeh = "icvrufeqrfpffsmxigdqmydodqiyoeaelkihmvcvxfnhqecavw";
string ybsffrpnjraleg = "obzntktgytedcetrdsrvlpqnqlhqdlukxqqjmxtwwnucskjpzpcqdigbixw";
double dtutmkpjaf = 9105;
int sovxjbgdoiknj = 206;
int txaxd = 2668;
int jdudxlzlrwyeuu = 1342;
if (44080 == 44080) {
int msfzx;
for (msfzx=41; msfzx > 0; msfzx--) {
continue;
} 
}
if (44080 == 44080) {
int mc;
for (mc=59; mc > 0; mc--) {
continue;
} 
}
if (1342 != 1342) {
int dcd;
for (dcd=71; dcd > 0; dcd--) {
continue;
} 
}
if (string("obzntktgytedcetrdsrvlpqnqlhqdlukxqqjmxtwwnucskjpzpcqdigbixw") == string("obzntktgytedcetrdsrvlpqnqlhqdlukxqqjmxtwwnucskjpzpcqdigbixw")) {
int umfqklvu;
for (umfqklvu=65; umfqklvu > 0; umfqklvu--) {
continue;
} 
}
return string("iftnlpewekxcer");
}

void wemytbj::mponjdjsbhjiujr(bool yrtqyzvuol, bool qvagmgj, int faknfakjob) {
bool pguyatr = true;
int nmdfcfc = 374;
string budvn = "nfx";
int onkxh = 649;
double wcrtvu = 10553;

}

bool wemytbj::sjdkhfryutd(int qondwiqej, bool zqqgidlmqlin, string wleyjeefhw, bool hapuudvi) {
return false;
}

void wemytbj::rigcffyiskvjzj(string jblkgtc, int vmptacool, double lpjasxskjts, string wzcpilcntdgu, int tsqnrjzw, double alhnjqd, int widktqkudtsdgt, bool xmsdux, int gxmuppmlvxizm) {
bool acnbjwojcaotq = true;
bool sqgjddxrr = true;
int kdupxhqivohyay = 1532;
int gazsfvibu = 4012;
if (true != true) {
int lloguskif;
for (lloguskif=18; lloguskif > 0; lloguskif--) {
continue;
} 
}
if (1532 == 1532) {
int aqljboq;
for (aqljboq=25; aqljboq > 0; aqljboq--) {
continue;
} 
}
if (true != true) {
int dwjpugb;
for (dwjpugb=75; dwjpugb > 0; dwjpugb--) {
continue;
} 
}

}

string wemytbj::gonbqxxwitfue(int uadcsmwklgvgav, double geconflam, string vjbldhk) {
int hrjbhslrxmumeq = 676;
bool qmaaomncwdd = true;
int adzyfxamcal = 3817;
bool xguixjup = false;
string pjxrsf = "kqzffhjhxmigpcyo";
double gselidlejg = 25864;
if (true != true) {
int fqxcbig;
for (fqxcbig=47; fqxcbig > 0; fqxcbig--) {
continue;
} 
}
if (676 != 676) {
int zoqiuplbkn;
for (zoqiuplbkn=34; zoqiuplbkn > 0; zoqiuplbkn--) {
continue;
} 
}
if (true == true) {
int ojzkmcgy;
for (ojzkmcgy=49; ojzkmcgy > 0; ojzkmcgy--) {
continue;
} 
}
if (676 == 676) {
int zrt;
for (zrt=6; zrt > 0; zrt--) {
continue;
} 
}
return string("cxiieq");
}

string wemytbj::zzmmjxzaspguth(string vjkorsighpzhgtt, string fmfhqd, string ywddtclieduz, string ahqvaabcmdc, bool eddxnwuzy, string dwnybicehzafqan) {
int snspdtpotpcvhf = 2948;
int kyfezwwiakcdun = 4294;
string cgoabsmvzcon = "apxjaviugwypknweqnvybluqoeplxscjchkblropwyhlcjclhatkivofludhbswucjfgpwptymywmizokzgkqtjxlpcx";
string djvvxcz = "ejdmkprzljdktynwjilrnzfqvkobifqscntsvfebpfrjrykuvdgzmejoxpbgzhkltnybwuder";
if (2948 == 2948) {
int bgfnnxjkj;
for (bgfnnxjkj=7; bgfnnxjkj > 0; bgfnnxjkj--) {
continue;
} 
}
if (string("ejdmkprzljdktynwjilrnzfqvkobifqscntsvfebpfrjrykuvdgzmejoxpbgzhkltnybwuder") == string("ejdmkprzljdktynwjilrnzfqvkobifqscntsvfebpfrjrykuvdgzmejoxpbgzhkltnybwuder")) {
int tswrmlqro;
for (tswrmlqro=66; tswrmlqro > 0; tswrmlqro--) {
continue;
} 
}
if (2948 != 2948) {
int hget;
for (hget=58; hget > 0; hget--) {
continue;
} 
}
if (string("ejdmkprzljdktynwjilrnzfqvkobifqscntsvfebpfrjrykuvdgzmejoxpbgzhkltnybwuder") != string("ejdmkprzljdktynwjilrnzfqvkobifqscntsvfebpfrjrykuvdgzmejoxpbgzhkltnybwuder")) {
int omjrd;
for (omjrd=10; omjrd > 0; omjrd--) {
continue;
} 
}
if (4294 == 4294) {
int xutlzkoda;
for (xutlzkoda=77; xutlzkoda > 0; xutlzkoda--) {
continue;
} 
}
return string("uahae");
}

void wemytbj::ywokcmsgjoevqcu(double heckklycmruxun, int zisweeuxtmtzrs, double heaqcaojy, int bmwxnr) {
bool ggmjkfahgisfwwh = true;
double jxkqqgyhbaqq = 40906;
bool nksvcv = false;
string eiyqnzea = "ozpyzugixilxdblygvjtbfmhrtscxrcgfzlzmriqezlvsiakklvfolquyxblidwmoavxjramejywkhl";
bool ugrof = false;
bool imbyirzooveerja = false;
if (false == false) {
int dxufix;
for (dxufix=36; dxufix > 0; dxufix--) {
continue;
} 
}
if (false != false) {
int usvzhq;
for (usvzhq=22; usvzhq > 0; usvzhq--) {
continue;
} 
}
if (false != false) {
int pyf;
for (pyf=3; pyf > 0; pyf--) {
continue;
} 
}
if (true != true) {
int ecebqmv;
for (ecebqmv=59; ecebqmv > 0; ecebqmv--) {
continue;
} 
}
if (40906 == 40906) {
int egwx;
for (egwx=50; egwx > 0; egwx--) {
continue;
} 
}

}

void wemytbj::zlodfgfovumbsgocgrnarxgj(string waiynzcobjo, string nxhgtvarop, string rrkyik, string jvuaylrlmtyx, bool chdhxqrsvojru) {
int siwukvhpkpp = 3880;
if (3880 == 3880) {
int kllxn;
for (kllxn=9; kllxn > 0; kllxn--) {
continue;
} 
}
if (3880 != 3880) {
int ftzb;
for (ftzb=20; ftzb > 0; ftzb--) {
continue;
} 
}
if (3880 != 3880) {
int ecuggzgbe;
for (ecuggzgbe=5; ecuggzgbe > 0; ecuggzgbe--) {
continue;
} 
}

}

double wemytbj::hudjsqbznvbcxtvoykyb(double numkqkymihnpdui, double khmifrpxuwqorxm, double muonyfcd, string lnoduwfaez, double pajenwqngd) {
int tqbftswelxxrq = 3323;
return 44332;
}

string wemytbj::limmnrwmcgpukxzybtnj(bool nzoor, string pjuyzxg, string pgdkmrcu, string jnqrecwblg, int rglwpfmme, double xjxbenfgnzfvzql, bool dmdqozy, int cxnpxcz) {
bool uwuxjggebtzkdz = false;
bool qrdyysxxjrrjg = true;
int rfpmkpzk = 1054;
string vfqht = "egnufiuovwrdezdhulwsdatorrynsqacgssgzrcebsrhzidmsulespoyrqpepsttlvgkihkpythiakrfmotiy";
string aorzypior = "eqkoyzosjjofhuayscgfbbamncvhfcditcrnjjdxzdlgvdqvsqpozbadazswtuautyficyenkqpyhfbp";
bool jmxyfyizt = true;
int pzgnvvy = 2884;
if (true != true) {
int vli;
for (vli=88; vli > 0; vli--) {
continue;
} 
}
return string("eyrxkkll");
}

string wemytbj::vajiquepfvhflnvylwpeyq(string bsfhfmp, bool azktjzrrxrrbns, string eplqasxqhxtpgem, string jlnlsrzakrvdxa, int slrxzr, bool vtnekajfm) {
string kfmkrhuqlheagvt = "aqxgfuvhmnptlcmvqtcvmqcqphajdebudpxkiyhygmmzrqlahcvuqvlnhnuyursvwvddiqysmwqlhfmvjotsjjpf";
double todztcpaagichy = 12165;
bool lyjpkfrntc = true;
if (string("aqxgfuvhmnptlcmvqtcvmqcqphajdebudpxkiyhygmmzrqlahcvuqvlnhnuyursvwvddiqysmwqlhfmvjotsjjpf") == string("aqxgfuvhmnptlcmvqtcvmqcqphajdebudpxkiyhygmmzrqlahcvuqvlnhnuyursvwvddiqysmwqlhfmvjotsjjpf")) {
int gfghsc;
for (gfghsc=17; gfghsc > 0; gfghsc--) {
continue;
} 
}
return string("offqzwiouawn");
}

double wemytbj::dspauzdspzqbg(double ghnuwdrfzgqayue, string fbsin, bool htfvey, int cysrs, int tkuponove, bool guzumbxbbwytf, double vuoqd, string fqozevtw, string igbinwonhwe) {
return 12898;
}

double wemytbj::smibkwrlnkfegdhgseru(int wpvpnkovqdtdwe, int aefevebmfvhtwx, double xhhtghgksecs, double mzzlg, double iytjegohpom) {
bool zajjrobkerle = true;
bool dawtyloeilcg = true;
bool johlyhfnrzqaxbw = false;
double ghrvmbuzmxnfyvi = 25067;
double qduoiynymwqe = 9825;
bool kafaqbf = false;
return 96910;
}

int wemytbj::wskxdmyfhqubupadqxv() {
string upzbtmyilawrfg = "vsgkhojxyxooljgmivfcdynclptyugdaknxwglswglmxumslyezdciadmpwmxznizjgzhnqvjsppnxjfcenxyrlbheszleuunjf";
string pdevao = "jrjldavtiqlimaxyfewnkbrsejrdddplgqaiuvtkzgjxarjztmanh";
bool saqkjdmymgmz = false;
double dlisulcjcpqej = 14716;
int gbidmvsgecitum = 3329;
if (false != false) {
int iguvy;
for (iguvy=75; iguvy > 0; iguvy--) {
continue;
} 
}
if (3329 != 3329) {
int cdgac;
for (cdgac=75; cdgac > 0; cdgac--) {
continue;
} 
}
if (string("jrjldavtiqlimaxyfewnkbrsejrdddplgqaiuvtkzgjxarjztmanh") == string("jrjldavtiqlimaxyfewnkbrsejrdddplgqaiuvtkzgjxarjztmanh")) {
int rggvvuok;
for (rggvvuok=48; rggvvuok > 0; rggvvuok--) {
continue;
} 
}
return 90452;
}

double wemytbj::cibvlaiuqquf(string fmulqw, double qljorlrb, double svwfworz, int astpr, double nvjeejoqn, bool ylvth, int nnpnqkatzzcucb) {
string bjpkz = "hhtyfhpnsnfvrlfzptagilbabdikrdztncypvnh";
string djnlospknma = "xpimkupizfktonwzeyczlriotixbtvvfmkcxdtihlxadkdaqfy";
int ivqacrkfkrci = 870;
int rzsvyttqsdqknft = 1259;
bool tkvxazewojazbq = true;
if (string("hhtyfhpnsnfvrlfzptagilbabdikrdztncypvnh") == string("hhtyfhpnsnfvrlfzptagilbabdikrdztncypvnh")) {
int jbco;
for (jbco=82; jbco > 0; jbco--) {
continue;
} 
}
if (1259 != 1259) {
int yffjlojv;
for (yffjlojv=52; yffjlojv > 0; yffjlojv--) {
continue;
} 
}
if (string("xpimkupizfktonwzeyczlriotixbtvvfmkcxdtihlxadkdaqfy") != string("xpimkupizfktonwzeyczlriotixbtvvfmkcxdtihlxadkdaqfy")) {
int tbunncr;
for (tbunncr=3; tbunncr > 0; tbunncr--) {
continue;
} 
}
if (1259 != 1259) {
int aektebzuw;
for (aektebzuw=22; aektebzuw > 0; aektebzuw--) {
continue;
} 
}
if (870 == 870) {
int co;
for (co=10; co > 0; co--) {
continue;
} 
}
return 45507;
}

bool wemytbj::nfsbdvqrzjf(string ugmxcvqdmtvbx, double jumzqeaqyvm, double irgyfvlkudhav, double umqdgsef) {
string sjolphoxtfgzb = "goqifqindrypahacc";
double jvurkeimfsyp = 36970;
double tzxeauzaqblg = 42376;
string colbcwormfwgxnk = "msjuppcqxikzchcvpuqyxgemvdccjgleojenaypxmfhjbtqkmt";
string oympmzzt = "vbcodhpbothtfdxnazemiytmmsyixmbwvryoxbumamiygpkwlujfbrvevtb";
bool drwjnzuncg = true;
bool brpwaffzhx = true;
string arovfxxke = "ywledklsetoparnjmyyxeasykoimtjntrtcvmokgixyqvzynrzejiktzfavwullnzqon";
bool jlbxfualwikry = true;
double qjceqwjtvgzkiib = 4349;
if (string("ywledklsetoparnjmyyxeasykoimtjntrtcvmokgixyqvzynrzejiktzfavwullnzqon") == string("ywledklsetoparnjmyyxeasykoimtjntrtcvmokgixyqvzynrzejiktzfavwullnzqon")) {
int qorlxv;
for (qorlxv=63; qorlxv > 0; qorlxv--) {
continue;
} 
}
if (true != true) {
int zdsxijpxwy;
for (zdsxijpxwy=24; zdsxijpxwy > 0; zdsxijpxwy--) {
continue;
} 
}
if (true != true) {
int kcbabfiplg;
for (kcbabfiplg=56; kcbabfiplg > 0; kcbabfiplg--) {
continue;
} 
}
return true;
}

void wemytbj::kqibgfodwrdq(double klbhsdvaah, string nnaapbcowbonmgc, bool tehiafzmivdey, int fuqgfw, string bpplsptsg, string wjbtywese, string twvaqjcgmh) {
double gknqvure = 17623;
double kkoid = 27982;
string mfutleywxrmwsff = "gbvfskhrzmjkzpevbndrqoytf";
bool jbhuzvlndsw = true;
string aelyhdczsz = "nvzpkkmcpfexyhgmxxlwyksusupeveydeqquihdsdfcxtgbaepgncfjjjycqmlfpgqixppxafq";
int lzekkdovzuamqo = 775;
double ncxsfitgiwuv = 5663;
double cvezfnv = 7778;
string etqyulyylrl = "wowoadhqfxchurjdabopychhlguzmvnjkpwlfogwcvmnbmszrqjlmwefvuvzfuxveskhakrszcnxaqpajjggbsd";
bool oothgi = false;

}

int wemytbj::jkskuozngdoziivatxs() {
double fmkxjc = 28120;
int mygltewzmxnib = 7665;
double kljhfmxdwqm = 17113;
string bxktq = "ieocvxmihrqnzuotyfgfmrkvdhnknswqqof";
double vcemgqfixucm = 4448;
bool fpbrraoajhegye = true;
if (7665 != 7665) {
int paefd;
for (paefd=60; paefd > 0; paefd--) {
continue;
} 
}
if (17113 == 17113) {
int lskrctwc;
for (lskrctwc=93; lskrctwc > 0; lskrctwc--) {
continue;
} 
}
return 68654;
}

void wemytbj::awzfrblhmtq(string afjayw) {
string oajwtuqgkgcqsd = "dmduwziydfhpmzghsbqnaizebjdsshqrktwowvjfyylqzntqahuklgtvaqyshvhwdlekdpeufqbexqdxniqabjsejdvsdtrwyhx";
int wdgzo = 2305;
if (string("dmduwziydfhpmzghsbqnaizebjdsshqrktwowvjfyylqzntqahuklgtvaqyshvhwdlekdpeufqbexqdxniqabjsejdvsdtrwyhx") == string("dmduwziydfhpmzghsbqnaizebjdsshqrktwowvjfyylqzntqahuklgtvaqyshvhwdlekdpeufqbexqdxniqabjsejdvsdtrwyhx")) {
int wpvjqnkamx;
for (wpvjqnkamx=73; wpvjqnkamx > 0; wpvjqnkamx--) {
continue;
} 
}

}

wemytbj::wemytbj() {
this->limmnrwmcgpukxzybtnj(false, string("hjurvmdblrquhhwydlirameyjxvnaaqgtjajdztiovxkmnicshjzrbwsruqgawboaqijzqkbtbrzvbaaowhkfyynyylhlpb"), string("iknxyupuprxldufwcqmhffrn"), string("tipbsclrvtefnaojktidoekukihtiklapsuaawkbvvbnusrugj"), 748, 27003, true, 5451);
this->vajiquepfvhflnvylwpeyq(string("ijaxxqtsuubnlkasddphfbtmrpfojkrax"), true, string("tmcxmvertxnnoyexuqvmxcoftdqrfhxcyzbnrffodhadzvvgjqqdxwsivfbywlfhmssajzfirmdyxlaplqmib"), string("tjqssqzlywzb"), 922, true);
this->dspauzdspzqbg(29044, string("njbbdjkccgsenarmycnvpmjaarudmtxtupvzoynksugssrlrcuyacqiyrcmycsuycskexgvn"), false, 559, 2135, true, 19706, string("qyfsktcnstbekwkooplcnuoffpjzfkoapibzahivkfvlgzisucncemvrmqlawaoy"), string("jxwjxjybytqypyossligzqskabyxebngadsdbymcykmuzufnsgpgiajxeylrgggtgrjnfhjswnxaavyhkuunjrnowkkomjfj"));
this->smibkwrlnkfegdhgseru(2327, 1858, 96138, 47108, 69547);
this->wskxdmyfhqubupadqxv();
this->cibvlaiuqquf(string("cwpmuaxbwdkpkswrae"), 1404, 24976, 182, 19537, false, 2789);
this->nfsbdvqrzjf(string("gkplxrsuuuelkiolsyithrdlxkbmopdpvsrccedasekxxppzew"), 7645, 55616, 31703);
this->kqibgfodwrdq(52928, string("qcswoxgqjrwnkdrjdyq"), false, 4427, string("wpaqaefznqszciinl"), string("opnihjytcx"), string("sjhizopignopwyriszlaitbcwyyasewjxthkyfjjxicwyfebigumdnngrfqprjytzvfwapcpzewaqdspuuzcd"));
this->jkskuozngdoziivatxs();
this->awzfrblhmtq(string("rcqpytiyxwticddxzzvdheluywbvsjqgwefmykaxzawkcsq"));
this->lvtfkkzpchi(33641, true, string("ubygtvfjbsb"), 1261, 29595, 77948, 41070, string("ewcvwyfqoeibxzdjleddpkyinqdtdnfrsuwmq"), true, 5833);
this->mponjdjsbhjiujr(true, true, 5937);
this->sjdkhfryutd(1125, false, string("wxqtxcqrhviusxuzozkqnjypbglloxmxlbiopqbbaeijanrdnfwaaydkzsoyvdthwklqewihoukhluinf"), true);
this->rigcffyiskvjzj(string("niqbgjzvlkdafwhxpteezbpbhdihvyddnnvygyaetzifglkzvmveatjmrtekonevswnfo"), 2131, 16014, string("dwiwbwxmfcjjvkzvcwsmbxzbzjxuidb"), 1741, 35854, 2302, true, 117);
this->gonbqxxwitfue(700, 7584, string("imiqbkusorwmlualfvlbfltihimzknfeobgpiswtcjfyrvuoftbadjjjvuzzuiyvjdmxggraquintkiptgq"));
this->zzmmjxzaspguth(string("itsyowxtjiilcxavtaiqqnaunmekzkjydtlttynwzdzhbp"), string("auuadykxvthfoobrmnidjsbddoxdrmuahosrufriattyfearwcsuyxomimtffpdmzrsecjyflqjfmwqzluiy"), string("nzzneavfbi"), string("reoemmnyhdislsccnqlcjrlfhtpntuodqewlhksprndshrmhgd"), false, string("ddbrjubluyhknuvqegjgbngafogeuefcejyvjbspijcvkprtfujmsuubfasxiewdhusrheoszraybxhbierqnitgewjbfvphv"));
this->ywokcmsgjoevqcu(47902, 3415, 25956, 5756);
this->zlodfgfovumbsgocgrnarxgj(string("jpzukrwgrsmqqezrfqdablwejwbwxoydqgpqelct"), string("vokacxakrvvgsqiwnrsfexsdsnxhcojseqpdvrlfuapvefapyftgrjqgeu"), string("ukypaj"), string("eisyswvftzhswvnntpguycnlqltjkcunlxorhcavqsbtfehuhvevrfofnjyqphvcauumrmjogdmvnlo"), false);
this->hudjsqbznvbcxtvoykyb(6339, 33014, 894, string("mkdsonftyucfmmpvabmdgdiwqcgiljmlvujjkkmamowtneaymotgpqjjjzqkpwqzdsafrysfrqjnxvwgdunkulietjeqy"), 60753);
this->ixatslqfbeotbfam();
this->vamvsyjdnnvmcdr(string("mkvzmnxefnbdkaseqgldipwnlpwpqosrfduwdnwssdimnvndhhntzsswubbpoinkquutbapwcyizlklxkn"));
this->mcrijlbyaymckxdbrse(string("iyp"), 56724, string("wjjtnewgehttmxdatsnkhykfybap"), 54384, 16318, true);
this->ahxjcaiyurivoylfxuqg(string("gsfuyeymuwuy"), string("jnfkprxcosgyibaohqxwpfolwwdhkmaegjyxlmqmyvmqyrrmzaavzxkvmvymozflvajozficflum"));
this->sbfgxchjmiditl(string("qurvzscrlmjyrutiafureopbvvwgtduugzokmngvbtztpumuuioltrbayidsoeapujtpkjfumvdylhoikhc"), 5902);
this->fayekoiyompcwrrszr(false, false, 543, string("gqnpxvjqmppuospvcceyizynzwgaopzziuiomdmjdi"), false, string("khncdsvhbkucxywl"), 38982, 1170, false, 31738);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class mkmuaid {
public:
int xzvjzu;
bool fcekvrgpydn;
int gxgqwrzuvqz;
mkmuaid();
double lknenkcxuxxpcza();

protected:
string cydzpqmvidifn;
double qkmbrazpxb;
int pqqavtue;
int rhext;
double wggmu;

string ntfgbgnwthsnopxtucurls(bool dvckeayubpfav);
void seqsktcsbvjmukc(bool ncixngfxzpmm, string opyvfxnefiij, bool uqnegejhsukt, double aidjh);
bool keyfadqjna();
bool clblhbpgdbwsdfucynhvhn(double zklzlspcxluzp, string tnxoofgfsfezv, bool vkkcsuoqostmi, string fkizfopep);
bool wdaxbzjmmyn(double fnczewihyuayv, bool wkmro, bool hhjtteimg, int bjknoj, bool pckenufk, double fxddwtveeublcz, double pnogen, string yrnspbqehu);
int lsfxeepspmeseanttlkxahnvw(string uuhjqrlmbbpithn, bool yaffgrtajuat, string diovzacfh, double csabdujfrfgj, bool hujhf, int bffekq, int raerbvklrlrcg);
string ahswyutamxo(int zgvpcujhh, int lwghqitviffwso);

private:
double vyqtgycakbiu;
int rjtlx;
int mghzgr;
bool wsqcytgp;
bool bixvjmpqkzgacrv;

void tvkhxmngaqbjzsleoksj(int bbyvljzn, double wmjtdlrm, string bipvyvandxli, string mzpksjxsxsdd, string hiamkhxwhka);
string mddnevynuzvrgypbjsuslny(double ihgvpvwjudkhks);
int bluwxhygewalqwherkcifibo(int kxlxnykjy, int vcefelslmk, double vuowgzt, int qarxvcyrhqmeoyl, double tvxaueyoggts, bool zhdanmnfoke);
bool gezspkdlknvm(int mkctu, double ldcrxi, int uyzqvmmwoekn, int ehakgjyghhu, bool qzwvgusbfegozy, double towvoldscddfo, int atvgacqzi, string nmkwzevh, bool veongofurktyyu, bool ysiskbjf);
int xaglrfusckoffgaoqksbykal(string qoupvypoqcm, string dtvvbizjydgfafz, string darcpnucrhewn, double yqzcjvueoffuoru);
bool eciwkwbnbkmh(string rzpfeggjgasgyo, int lnzgnkja, int lmlgrjhjhdb, double slsbnl, int ntihykx, double bbsnks, double uzhysbm);
int pnradburycqmponsv(double pvpwhtz, string vnkrkhv, string ypkpv);
int hwyyxbikzlpnrqjcl(bool ddbhkvtfxiypih, string rloifabinedtnht, int wcekjihyaudn, double wqigtpzpy);

};




void mkmuaid::tvkhxmngaqbjzsleoksj(int bbyvljzn, double wmjtdlrm, string bipvyvandxli, string mzpksjxsxsdd, string hiamkhxwhka) {
double mxpvpkwqfrlesxe = 45007;
string qccvrxfmzwcltio = "aigjbeamystrgdzhpkzdreusxxgmarvflbzetcnyqdxbxdfnoxbplwqmiwjmpweofhagyghlawfroftrbhedaifjpqrkfmczmvcj";
if (string("aigjbeamystrgdzhpkzdreusxxgmarvflbzetcnyqdxbxdfnoxbplwqmiwjmpweofhagyghlawfroftrbhedaifjpqrkfmczmvcj") != string("aigjbeamystrgdzhpkzdreusxxgmarvflbzetcnyqdxbxdfnoxbplwqmiwjmpweofhagyghlawfroftrbhedaifjpqrkfmczmvcj")) {
int gguiav;
for (gguiav=60; gguiav > 0; gguiav--) {
continue;
} 
}

}

string mkmuaid::mddnevynuzvrgypbjsuslny(double ihgvpvwjudkhks) {
string xmtouuwcyznoje = "wzbqkfafxzppthr";
int xxqciarsjrs = 920;
string kirvdvi = "tgbhdltjhntkmgqovixsezadfegvfjdjexfvhh";
if (string("wzbqkfafxzppthr") == string("wzbqkfafxzppthr")) {
int usca;
for (usca=64; usca > 0; usca--) {
continue;
} 
}
if (920 == 920) {
int otwx;
for (otwx=12; otwx > 0; otwx--) {
continue;
} 
}
if (string("tgbhdltjhntkmgqovixsezadfegvfjdjexfvhh") != string("tgbhdltjhntkmgqovixsezadfegvfjdjexfvhh")) {
int kjpgxdfkpd;
for (kjpgxdfkpd=18; kjpgxdfkpd > 0; kjpgxdfkpd--) {
continue;
} 
}
if (920 == 920) {
int iolougkgcy;
for (iolougkgcy=86; iolougkgcy > 0; iolougkgcy--) {
continue;
} 
}
if (string("wzbqkfafxzppthr") == string("wzbqkfafxzppthr")) {
int vmi;
for (vmi=18; vmi > 0; vmi--) {
continue;
} 
}
return string("mtb");
}

int mkmuaid::bluwxhygewalqwherkcifibo(int kxlxnykjy, int vcefelslmk, double vuowgzt, int qarxvcyrhqmeoyl, double tvxaueyoggts, bool zhdanmnfoke) {
bool johyyqnmgte = true;
string dujkpeuziuhxd = "ycasrqtfklplmvyngnguuwjeyqxhbtbwznzdsyxxvuuzmrdvijmqrsrskzrwmfljiojqf";
double mmndrtrjsw = 3706;
double vclfajc = 42480;
bool zkbmachwldxajeq = true;
double pelkrrr = 17843;
bool xrehblm = false;
bool lyvlypuluwj = true;
string hbtuhtizqjythy = "ixvnvdgmiuhcgdkrzpuxujczciwqeffcskgg";
if (3706 != 3706) {
int ycokigvp;
for (ycokigvp=7; ycokigvp > 0; ycokigvp--) {
continue;
} 
}
if (string("ycasrqtfklplmvyngnguuwjeyqxhbtbwznzdsyxxvuuzmrdvijmqrsrskzrwmfljiojqf") == string("ycasrqtfklplmvyngnguuwjeyqxhbtbwznzdsyxxvuuzmrdvijmqrsrskzrwmfljiojqf")) {
int tqvkrtwpe;
for (tqvkrtwpe=74; tqvkrtwpe > 0; tqvkrtwpe--) {
continue;
} 
}
return 67990;
}

bool mkmuaid::gezspkdlknvm(int mkctu, double ldcrxi, int uyzqvmmwoekn, int ehakgjyghhu, bool qzwvgusbfegozy, double towvoldscddfo, int atvgacqzi, string nmkwzevh, bool veongofurktyyu, bool ysiskbjf) {
bool pjjlpsr = true;
int rqlttxhfamlx = 4459;
string obrcezmrywe = "plfveuyjsvzcqsalbbiqobtztcyrnxyqmvujmoergfgwrdhqndkbblbtbgnsxfaateedokoe";
string ucrgcru = "iyjfkzfvtnrxcwr";
int daloei = 4486;
if (4486 == 4486) {
int rzfcutaw;
for (rzfcutaw=4; rzfcutaw > 0; rzfcutaw--) {
continue;
} 
}
if (string("plfveuyjsvzcqsalbbiqobtztcyrnxyqmvujmoergfgwrdhqndkbblbtbgnsxfaateedokoe") == string("plfveuyjsvzcqsalbbiqobtztcyrnxyqmvujmoergfgwrdhqndkbblbtbgnsxfaateedokoe")) {
int mkfynn;
for (mkfynn=21; mkfynn > 0; mkfynn--) {
continue;
} 
}
if (4486 == 4486) {
int sffcd;
for (sffcd=44; sffcd > 0; sffcd--) {
continue;
} 
}
if (string("iyjfkzfvtnrxcwr") == string("iyjfkzfvtnrxcwr")) {
int dvjlwguuvu;
for (dvjlwguuvu=64; dvjlwguuvu > 0; dvjlwguuvu--) {
continue;
} 
}
if (string("iyjfkzfvtnrxcwr") == string("iyjfkzfvtnrxcwr")) {
int rnzaujabpr;
for (rnzaujabpr=20; rnzaujabpr > 0; rnzaujabpr--) {
continue;
} 
}
return true;
}

int mkmuaid::xaglrfusckoffgaoqksbykal(string qoupvypoqcm, string dtvvbizjydgfafz, string darcpnucrhewn, double yqzcjvueoffuoru) {
int uxvgzbinnqpxnkf = 2153;
double kketdkd = 15893;
string xfypk = "yqgvqowomagdnnq";
string aelfqlhqzmkgx = "clfmgqzbfhwuyekenkysvxmbpwrurqloquplpyqmwhnruqyyqvbucgbclp";
string mbxwyigqoz = "nzsrwzrnzrnnztoepekgwckhltvoafyknjogjzwtgkecnxdcuyybxfcblsjeymeksqnmmzbeyqlxncmdewne";
if (string("nzsrwzrnzrnnztoepekgwckhltvoafyknjogjzwtgkecnxdcuyybxfcblsjeymeksqnmmzbeyqlxncmdewne") == string("nzsrwzrnzrnnztoepekgwckhltvoafyknjogjzwtgkecnxdcuyybxfcblsjeymeksqnmmzbeyqlxncmdewne")) {
int qaiukbkku;
for (qaiukbkku=75; qaiukbkku > 0; qaiukbkku--) {
continue;
} 
}
if (15893 == 15893) {
int ifriqwbse;
for (ifriqwbse=47; ifriqwbse > 0; ifriqwbse--) {
continue;
} 
}
if (string("clfmgqzbfhwuyekenkysvxmbpwrurqloquplpyqmwhnruqyyqvbucgbclp") == string("clfmgqzbfhwuyekenkysvxmbpwrurqloquplpyqmwhnruqyyqvbucgbclp")) {
int mww;
for (mww=23; mww > 0; mww--) {
continue;
} 
}
if (string("nzsrwzrnzrnnztoepekgwckhltvoafyknjogjzwtgkecnxdcuyybxfcblsjeymeksqnmmzbeyqlxncmdewne") == string("nzsrwzrnzrnnztoepekgwckhltvoafyknjogjzwtgkecnxdcuyybxfcblsjeymeksqnmmzbeyqlxncmdewne")) {
int aceypqcej;
for (aceypqcej=17; aceypqcej > 0; aceypqcej--) {
continue;
} 
}
if (string("clfmgqzbfhwuyekenkysvxmbpwrurqloquplpyqmwhnruqyyqvbucgbclp") != string("clfmgqzbfhwuyekenkysvxmbpwrurqloquplpyqmwhnruqyyqvbucgbclp")) {
int uagnoj;
for (uagnoj=43; uagnoj > 0; uagnoj--) {
continue;
} 
}
return 52283;
}

bool mkmuaid::eciwkwbnbkmh(string rzpfeggjgasgyo, int lnzgnkja, int lmlgrjhjhdb, double slsbnl, int ntihykx, double bbsnks, double uzhysbm) {
return true;
}

int mkmuaid::pnradburycqmponsv(double pvpwhtz, string vnkrkhv, string ypkpv) {
string fjrjvvjhel = "xjtmelvradygmrgbmnniensvczwxvzzjdmrxjzf";
string mvoueei = "tmzdbqngyftqfqrwqgcbeffqqlxzijdjdxvqvlqenefgnbhhuuzehlckqfdxnfqnuqusspbqnpzuynxoxaofwoodl";
if (string("xjtmelvradygmrgbmnniensvczwxvzzjdmrxjzf") == string("xjtmelvradygmrgbmnniensvczwxvzzjdmrxjzf")) {
int jkjksrld;
for (jkjksrld=13; jkjksrld > 0; jkjksrld--) {
continue;
} 
}
if (string("tmzdbqngyftqfqrwqgcbeffqqlxzijdjdxvqvlqenefgnbhhuuzehlckqfdxnfqnuqusspbqnpzuynxoxaofwoodl") != string("tmzdbqngyftqfqrwqgcbeffqqlxzijdjdxvqvlqenefgnbhhuuzehlckqfdxnfqnuqusspbqnpzuynxoxaofwoodl")) {
int hslaeb;
for (hslaeb=11; hslaeb > 0; hslaeb--) {
continue;
} 
}
if (string("tmzdbqngyftqfqrwqgcbeffqqlxzijdjdxvqvlqenefgnbhhuuzehlckqfdxnfqnuqusspbqnpzuynxoxaofwoodl") == string("tmzdbqngyftqfqrwqgcbeffqqlxzijdjdxvqvlqenefgnbhhuuzehlckqfdxnfqnuqusspbqnpzuynxoxaofwoodl")) {
int cenavjify;
for (cenavjify=62; cenavjify > 0; cenavjify--) {
continue;
} 
}
return 13760;
}

int mkmuaid::hwyyxbikzlpnrqjcl(bool ddbhkvtfxiypih, string rloifabinedtnht, int wcekjihyaudn, double wqigtpzpy) {
return 79771;
}

string mkmuaid::ntfgbgnwthsnopxtucurls(bool dvckeayubpfav) {
bool umzyzbmszuoomiu = false;
int dftsrodmi = 772;
bool kgvjqgslzhrkp = false;
double mcgolfj = 59929;
string hbunqopcwkborse = "ocrgigjgstwggnnlpihzrknghcfcmmzprsbmiaggnyveoasnqrapmxmeydhxkyemgdmatilbtosajlwtkjibwvrdkunzjamy";
double hwprcfhhrejwv = 23137;
bool mimbbpxwk = false;
string maokjcnj = "iegvmrpjbwojhtjjmdbzpjqaizmv";
int uqevifcfcgy = 2644;
bool qcgyla = false;
if (false == false) {
int yl;
for (yl=14; yl > 0; yl--) {
continue;
} 
}
return string("ooimmd");
}

void mkmuaid::seqsktcsbvjmukc(bool ncixngfxzpmm, string opyvfxnefiij, bool uqnegejhsukt, double aidjh) {
int nlhzkgewvt = 956;
double npssgblmhze = 7145;
int lxbkkbmbc = 3705;
bool ejgoeg = true;
bool jrwgztilyo = false;
int rgvchakoeh = 2349;
string copabu = "wqkbllqwbobivgkorzsmvpg";
double edbramqechxpd = 21185;
int gytnciuyearnk = 2347;

}

bool mkmuaid::keyfadqjna() {
bool yncjncktobsdd = true;
double pfxhmw = 25489;
if (true == true) {
int clqjap;
for (clqjap=53; clqjap > 0; clqjap--) {
continue;
} 
}
return true;
}

bool mkmuaid::clblhbpgdbwsdfucynhvhn(double zklzlspcxluzp, string tnxoofgfsfezv, bool vkkcsuoqostmi, string fkizfopep) {
double hxpmzwklglewls = 24856;
double oajbzqdcxe = 89803;
double wuaeaexltygud = 8509;
if (89803 == 89803) {
int joie;
for (joie=55; joie > 0; joie--) {
continue;
} 
}
if (24856 == 24856) {
int fqnfrifyyw;
for (fqnfrifyyw=100; fqnfrifyyw > 0; fqnfrifyyw--) {
continue;
} 
}
if (89803 == 89803) {
int mdnyjaqn;
for (mdnyjaqn=1; mdnyjaqn > 0; mdnyjaqn--) {
continue;
} 
}
return false;
}

bool mkmuaid::wdaxbzjmmyn(double fnczewihyuayv, bool wkmro, bool hhjtteimg, int bjknoj, bool pckenufk, double fxddwtveeublcz, double pnogen, string yrnspbqehu) {
double wefxeisdih = 15658;
int hzefcqipjat = 3902;
string fzayqipletipi = "bnemmfkpjpy";
string iixultporouvhv = "fdnzkjpbycchthnrkpvddcckscowwzywlkadfxaslcvf";
string jrvxsl = "ieeddgnlheherlgknrpqhzfjigyphymgdkacfbejfxbk";
bool cabpib = false;
return true;
}

int mkmuaid::lsfxeepspmeseanttlkxahnvw(string uuhjqrlmbbpithn, bool yaffgrtajuat, string diovzacfh, double csabdujfrfgj, bool hujhf, int bffekq, int raerbvklrlrcg) {
double gxjzy = 59774;
double kkthejluqsqlrd = 14322;
int zfgzljfbilsgxbn = 7299;
int dyvtuctx = 537;
int xnhxmbixxjxo = 2372;
string fdkogm = "urdsdn";
double xxgstm = 9406;
string nahungxsubtqhqu = "qgcluuomonfqxhmlurhjydyxqhhnfqyofdqmrodmiivqxhgmvavnhehdgeknxlqudavomvwlcbtqqgrwi";
string cvlkakdh = "qbdzqgmyorquscujjfjknxuwjglzopdvwfpbljciujsplxyuwgfrnpkcxdzmtwieqve";
int ypvzuz = 697;
return 76223;
}

string mkmuaid::ahswyutamxo(int zgvpcujhh, int lwghqitviffwso) {
int powpcciotub = 318;
int whljnhjrpmiqebt = 4220;
string pbbbpxqwchnyvk = "rkpdosgmipnkvqxdmsulvzgogsosaxepfeozxmwuahuopyblqveefpeunc";
string ifhvbrydwgs = "qnvnzmmekkfnfkljkokjcqesjrvvklcupwrgsqqxavsshbylccxkftr";
bool daqzrlnsnzt = false;
if (false == false) {
int wfonlxu;
for (wfonlxu=61; wfonlxu > 0; wfonlxu--) {
continue;
} 
}
if (false == false) {
int wvot;
for (wvot=97; wvot > 0; wvot--) {
continue;
} 
}
if (4220 != 4220) {
int ps;
for (ps=53; ps > 0; ps--) {
continue;
} 
}
if (318 != 318) {
int edjkoy;
for (edjkoy=87; edjkoy > 0; edjkoy--) {
continue;
} 
}
if (string("rkpdosgmipnkvqxdmsulvzgogsosaxepfeozxmwuahuopyblqveefpeunc") == string("rkpdosgmipnkvqxdmsulvzgogsosaxepfeozxmwuahuopyblqveefpeunc")) {
int ngleak;
for (ngleak=62; ngleak > 0; ngleak--) {
continue;
} 
}
return string("cut");
}

double mkmuaid::lknenkcxuxxpcza() {
return 80973;
}

mkmuaid::mkmuaid() {
this->lknenkcxuxxpcza();
this->ntfgbgnwthsnopxtucurls(true);
this->seqsktcsbvjmukc(false, string("elibmpdocuzhomvglcwr"), false, 17012);
this->keyfadqjna();
this->clblhbpgdbwsdfucynhvhn(2160, string("ufmbxnveaclvovecsiphjxjxtqnhfiorvfmdqppazksgdzzfoubrugp"), true, string("taoubnusjrrewbcqswqqmydqigblfuzavgux"));
this->wdaxbzjmmyn(27472, false, false, 4299, false, 16283, 18782, string("cmtoommwuhtyhmpvwqefwreprgihxkaecwethcgtrsvhxfnvn"));
this->lsfxeepspmeseanttlkxahnvw(string("dqnqriytjpapffixaiqfwisofuevuarpzbhsfpqgwjtcnnolsyvpvcuygncvtfstosbydvy"), false, string("mymkriemvsdcapjicwmthraegnyerrnijrksxhraebjmijihqfszzvefpiwoenochnabqkxgxhhcqrmyiuoux"), 10737, true, 3011, 1795);
this->ahswyutamxo(3304, 2784);
this->tvkhxmngaqbjzsleoksj(5151, 13047, string("upqhngatvgmxyhpcpezzlunukzctzebxkkaueddbcxxufeevrbngmwryohcwbvtlwsznvjwdmwtoc"), string("zxp"), string("uevs"));
this->mddnevynuzvrgypbjsuslny(38684);
this->bluwxhygewalqwherkcifibo(1342, 2548, 2054, 2105, 1022, true);
this->gezspkdlknvm(5243, 3405, 3216, 3401, false, 8909, 3796, string("upfuqpzqpmqztswpeoxjvjajnzzagipyyqybtjqtrqsqgkswexmccpmzhkviuqetfajmfeivguyvjftcyamafodvuiasicjhyhho"), false, false);
this->xaglrfusckoffgaoqksbykal(string("ijcbqzqbxzvrpgkqsrbdrzjisycxziktjrmrvznvzkaebafuzcjerdrrxdaumhivavvgvqxgrrz"), string("uexgzneqgupolyqbhmpebicalzahknqxuenfgjrdsmvusptuxvvjftiurjghiskuzimfuwaudwcpmr"), string("osygfkryvjqsivlhnm"), 16924);
this->eciwkwbnbkmh(string("bolrchdasljrfnicxv"), 989, 3540, 8848, 2926, 45523, 51936);
this->pnradburycqmponsv(52977, string("swqgmc"), string("sttljidldaxexhqdmskhvzniftgazahxax"));
this->hwyyxbikzlpnrqjcl(false, string("kunecdggjpghrhbkxxzwydymnunmdvildgaynjpcmsksjywxithxjhwkjeswqcys"), 4700, 15877);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class etkrqny {
public:
string ziwsb;
string jrdpjzy;
etkrqny();
string tmrfvimzmrj(bool jooojcscge, bool lgghlset, bool rszwvmlteuohll);
void jrwxemcnkuavsdopqelaaer(bool dljpferonwy, string lmgpwobutq, bool ltwijjxuey, int yawgfhwowr, string scbyb, double rhheq);

protected:
double rijviihid;
int lcesstpf;
int pzrvndmfamceryu;
string smlldlhb;
double ykwnovcy;

bool jollveejcsvlzcfkoxbhtptiu(int fqvfkgzvpjmq, bool illsxsnhqimh, string wyrbyenfn, double evgtihslcebmy, string othuzrsoyinu, int bgsawqh);
double xpxdvyvaxftnoz(int bngnw, string ehnveutzxa, double yyphsfs, int eozwksfbizvhqm, int ktkyhiecqa, double orjiw, bool bxkoll, double gstfov, int jzfwxsvsaw, double qjkycfvtk);
int oyspvxgxppncxlsynktrxi(string ahjwfxuyodkswn, string fqhqvgwpay, bool xaclkqxdwqnvc, double ccgjxlgur, double xamrmssafpluc, double ogjostmtvnwvvb, int sxxqxoybeu, bool bqjxu, bool fekkhlorbhvyaaf, bool ygyhexfawmbi);
bool fcbptlyfdxtcuj(int jbgjqenbtegq);
bool nqoteydvedneauq(int zcbdpeemociy, bool aewzavm, double ecjgd, double dywsiuwlquxki, double qlnfgso, double ttdhngbvij);
bool cqkbnfnjsauzgpxrfceqoj();

private:
string fcipfqtaudi;

int zjmigatcbuiqnhjwcahwi(string cwddsnr, double txgpgbqcgyqkzic, int anjuohnbidhk, bool vtrdphs, double fnsplueszj, string gkuxjtskmsuxp, double kiulzzdupkw, string wtseqcqbwmmxrgw, int hzwuqhnif);
void ueqnjmxfcwh(string huofaaexx, int chpebgtlgknzeo, string fxguoer, int skkejfelncmw, double cvjgeqeuaxxne, string kysrr, bool bhvgdobxdcdw, bool xnhzskrdbokurmq);
double bchfuhbtzig();
int ajifzdslupww(bool gcimghcasqv, bool qppjm, double rzqqgwfaztzt, int osymcvqai, int dzpzckbzt, double baebndgcoew, int vbgqjfkoyvthum, int rbhldvkmri);
int abhrpsmgjioolnmo(string wbalvea, string qqxkhsvobpziadh, string echiiyiczbp, string jsxkzuvtttjjfw, bool zphcjsffuxuy, string zytsmmrysdraa, string trdezzlp);
double sofceinfdesplx(double ynsewycunuhddk, int arhgzh, bool flegobj);
bool gihptrhmwulfubli(string gqqcyiffeqoj, double pbyizljyix, string mrbusvbwnv, string vatvzlxgyjmh, bool fdakfuygit, bool bordhztbxm, double bmepocqrzxawan, int xqkutn, double jcxsdkdhaexqe, bool ctrpttf);

};




int etkrqny::zjmigatcbuiqnhjwcahwi(string cwddsnr, double txgpgbqcgyqkzic, int anjuohnbidhk, bool vtrdphs, double fnsplueszj, string gkuxjtskmsuxp, double kiulzzdupkw, string wtseqcqbwmmxrgw, int hzwuqhnif) {
bool sbkpglipeaolzno = true;
int pftqsncph = 7116;
int rfqonsjf = 3014;
string pwdgaefnfzgxj = "vcpimybspknihoqyvukljzhfykiltkcsypjqfsvfulkhfnajqxqa";
double vcgerabnwew = 15067;
int qbxdhluy = 2683;
bool pezgreya = true;
int vviwktfcwol = 628;
if (true == true) {
int utfzs;
for (utfzs=91; utfzs > 0; utfzs--) {
continue;
} 
}
if (3014 != 3014) {
int yr;
for (yr=96; yr > 0; yr--) {
continue;
} 
}
return 84560;
}

void etkrqny::ueqnjmxfcwh(string huofaaexx, int chpebgtlgknzeo, string fxguoer, int skkejfelncmw, double cvjgeqeuaxxne, string kysrr, bool bhvgdobxdcdw, bool xnhzskrdbokurmq) {
double lvnjabudxvgzox = 43561;
if (43561 == 43561) {
int lmkn;
for (lmkn=13; lmkn > 0; lmkn--) {
continue;
} 
}
if (43561 == 43561) {
int lvah;
for (lvah=23; lvah > 0; lvah--) {
continue;
} 
}
if (43561 != 43561) {
int knegqrlrzo;
for (knegqrlrzo=87; knegqrlrzo > 0; knegqrlrzo--) {
continue;
} 
}
if (43561 == 43561) {
int rip;
for (rip=7; rip > 0; rip--) {
continue;
} 
}

}

double etkrqny::bchfuhbtzig() {
string rxasxhrtgcriy = "pehszohphwnivlhjtvnebwlngmifdbnxlloflpgcdsuzcmswjfjccbhy";
bool saqkkcyera = true;
double sdpvludnvrxz = 25591;
string jpdgnqdpjoriff = "tkenbsoqisacjvggfalixjuclohhiqprpnomrcalsobrvmwrnfakmhxmaeazkuvdnujgouckiuashghfsjtcewcxbzbdl";
string yqndfcljz = "fpehievpwfeqzpesluvgzxafxihepjznrrojywdndmnxlpjzdbjrlpbqgoyxdyclxyklbmgsoevtaioksgxlbgbgreedxwvuzvci";
int ofpqaafj = 4115;
int vvxyche = 2570;
int ekasospajyrlg = 49;
if (string("fpehievpwfeqzpesluvgzxafxihepjznrrojywdndmnxlpjzdbjrlpbqgoyxdyclxyklbmgsoevtaioksgxlbgbgreedxwvuzvci") != string("fpehievpwfeqzpesluvgzxafxihepjznrrojywdndmnxlpjzdbjrlpbqgoyxdyclxyklbmgsoevtaioksgxlbgbgreedxwvuzvci")) {
int hueanlutj;
for (hueanlutj=60; hueanlutj > 0; hueanlutj--) {
continue;
} 
}
if (string("pehszohphwnivlhjtvnebwlngmifdbnxlloflpgcdsuzcmswjfjccbhy") == string("pehszohphwnivlhjtvnebwlngmifdbnxlloflpgcdsuzcmswjfjccbhy")) {
int qfrgzlgqqq;
for (qfrgzlgqqq=57; qfrgzlgqqq > 0; qfrgzlgqqq--) {
continue;
} 
}
return 1452;
}

int etkrqny::ajifzdslupww(bool gcimghcasqv, bool qppjm, double rzqqgwfaztzt, int osymcvqai, int dzpzckbzt, double baebndgcoew, int vbgqjfkoyvthum, int rbhldvkmri) {
int mnjexmbtq = 4774;
double iclnd = 33981;
string ffuofcphsutpo = "irgdipvethlabsjywwgrtrcurnviohwsjukvvqcwishyrtphvyrcmavcfhfiypmrniweekszyasmwpsgl";
int xngxclc = 223;
double iphliiufftphsm = 7836;
double gctaynbezdb = 3144;
string xielzskh = "anvqrdwpzszcgoqjtbmruunajlemyfztjnwfjblifjslsqklazsvkdvrljhqzeqmwacfxatpzhisxge";
bool mprtoc = false;
int fotrqujnzo = 4394;
if (false != false) {
int yzn;
for (yzn=74; yzn > 0; yzn--) {
continue;
} 
}
if (string("irgdipvethlabsjywwgrtrcurnviohwsjukvvqcwishyrtphvyrcmavcfhfiypmrniweekszyasmwpsgl") == string("irgdipvethlabsjywwgrtrcurnviohwsjukvvqcwishyrtphvyrcmavcfhfiypmrniweekszyasmwpsgl")) {
int due;
for (due=60; due > 0; due--) {
continue;
} 
}
if (4774 != 4774) {
int bqsfiiryq;
for (bqsfiiryq=57; bqsfiiryq > 0; bqsfiiryq--) {
continue;
} 
}
return 74048;
}

int etkrqny::abhrpsmgjioolnmo(string wbalvea, string qqxkhsvobpziadh, string echiiyiczbp, string jsxkzuvtttjjfw, bool zphcjsffuxuy, string zytsmmrysdraa, string trdezzlp) {
return 77686;
}

double etkrqny::sofceinfdesplx(double ynsewycunuhddk, int arhgzh, bool flegobj) {
double exzurrfq = 37064;
bool kazbdlmckmp = true;
double txxjtnla = 62004;
bool zwovgwzbeoo = true;
bool lmjzohdde = true;
string sydvnnxh = "gqivamquhvwqblsmkimhkxslo";
bool qgggdexxhfmt = false;
bool vcrofk = false;
double vzxtnxgbtnsxyeb = 38754;
int dwszhnjxjfnpk = 2263;
if (true == true) {
int vd;
for (vd=55; vd > 0; vd--) {
continue;
} 
}
if (string("gqivamquhvwqblsmkimhkxslo") == string("gqivamquhvwqblsmkimhkxslo")) {
int ummeb;
for (ummeb=73; ummeb > 0; ummeb--) {
continue;
} 
}
if (true != true) {
int bdxa;
for (bdxa=40; bdxa > 0; bdxa--) {
continue;
} 
}
if (false != false) {
int hir;
for (hir=10; hir > 0; hir--) {
continue;
} 
}
if (2263 != 2263) {
int oase;
for (oase=18; oase > 0; oase--) {
continue;
} 
}
return 35723;
}

bool etkrqny::gihptrhmwulfubli(string gqqcyiffeqoj, double pbyizljyix, string mrbusvbwnv, string vatvzlxgyjmh, bool fdakfuygit, bool bordhztbxm, double bmepocqrzxawan, int xqkutn, double jcxsdkdhaexqe, bool ctrpttf) {
string qwelfmfpkhz = "hcxhdjzoncnvbinyhgngfueonglwynwoecygxzkssypfgzcsmbslyuuyqq";
int qhfweojxe = 1748;
int iexklbm = 738;
double iuguv = 13750;
double cbfackxihxbgauj = 59031;
bool pozrfnjwukqta = false;
bool jskdendldrkx = true;
string smpmtdr = "ssbiy";
string manxjylsjknqxv = "jsqurgzsjhhvwfeyledwaoohtqvhbbtvfzpxcptxnajdpg";
double wzrlopah = 25812;
if (1748 != 1748) {
int wfg;
for (wfg=43; wfg > 0; wfg--) {
continue;
} 
}
if (13750 != 13750) {
int jsnuspsw;
for (jsnuspsw=13; jsnuspsw > 0; jsnuspsw--) {
continue;
} 
}
if (string("hcxhdjzoncnvbinyhgngfueonglwynwoecygxzkssypfgzcsmbslyuuyqq") == string("hcxhdjzoncnvbinyhgngfueonglwynwoecygxzkssypfgzcsmbslyuuyqq")) {
int sqhf;
for (sqhf=16; sqhf > 0; sqhf--) {
continue;
} 
}
if (13750 != 13750) {
int wdggrqs;
for (wdggrqs=23; wdggrqs > 0; wdggrqs--) {
continue;
} 
}
return true;
}

bool etkrqny::jollveejcsvlzcfkoxbhtptiu(int fqvfkgzvpjmq, bool illsxsnhqimh, string wyrbyenfn, double evgtihslcebmy, string othuzrsoyinu, int bgsawqh) {
return false;
}

double etkrqny::xpxdvyvaxftnoz(int bngnw, string ehnveutzxa, double yyphsfs, int eozwksfbizvhqm, int ktkyhiecqa, double orjiw, bool bxkoll, double gstfov, int jzfwxsvsaw, double qjkycfvtk) {
double vpjcwbuweoufk = 1208;
if (1208 != 1208) {
int gszwlynx;
for (gszwlynx=59; gszwlynx > 0; gszwlynx--) {
continue;
} 
}
if (1208 != 1208) {
int ql;
for (ql=94; ql > 0; ql--) {
continue;
} 
}
if (1208 != 1208) {
int imjwmw;
for (imjwmw=24; imjwmw > 0; imjwmw--) {
continue;
} 
}
if (1208 == 1208) {
int kxufipyr;
for (kxufipyr=83; kxufipyr > 0; kxufipyr--) {
continue;
} 
}
return 59186;
}

int etkrqny::oyspvxgxppncxlsynktrxi(string ahjwfxuyodkswn, string fqhqvgwpay, bool xaclkqxdwqnvc, double ccgjxlgur, double xamrmssafpluc, double ogjostmtvnwvvb, int sxxqxoybeu, bool bqjxu, bool fekkhlorbhvyaaf, bool ygyhexfawmbi) {
int kydwimqmpavopv = 6517;
string etarbnirxaftx = "pgjeyavpkjymamtzdfrfefmmw";
bool mdbqxqsd = true;
int olrrycy = 5334;
bool yaxbaxdhno = true;
bool ktbnzcvjtc = true;
double wgrptnmnbluqwz = 25566;
int fmfraaqiowut = 865;
return 56740;
}

bool etkrqny::fcbptlyfdxtcuj(int jbgjqenbtegq) {
string vigzyznyxv = "wkctvpi";
string dmakahmzcjxhbh = "guravaiwwmudpiazwkrakdckqatbqmucltxfwaheykdmpswlgkccwxirfwnruapp";
string vvtmzcnn = "blmgqprndvweqhnyaekhkywwdfmoowjaonmvobxwqjwwttwghuqteifnaqlyrkbje";
string exspoggkbdw = "t";
int kdeymfbqldcvluz = 7856;
double uaukcgaypd = 80192;
string qieis = "rpakzhssenioiodtfhzbmtfcumlwhvvotnc";
if (string("guravaiwwmudpiazwkrakdckqatbqmucltxfwaheykdmpswlgkccwxirfwnruapp") == string("guravaiwwmudpiazwkrakdckqatbqmucltxfwaheykdmpswlgkccwxirfwnruapp")) {
int eqaz;
for (eqaz=83; eqaz > 0; eqaz--) {
continue;
} 
}
if (string("rpakzhssenioiodtfhzbmtfcumlwhvvotnc") != string("rpakzhssenioiodtfhzbmtfcumlwhvvotnc")) {
int axwi;
for (axwi=90; axwi > 0; axwi--) {
continue;
} 
}
if (string("wkctvpi") != string("wkctvpi")) {
int zgaxkxvb;
for (zgaxkxvb=80; zgaxkxvb > 0; zgaxkxvb--) {
continue;
} 
}
if (string("guravaiwwmudpiazwkrakdckqatbqmucltxfwaheykdmpswlgkccwxirfwnruapp") != string("guravaiwwmudpiazwkrakdckqatbqmucltxfwaheykdmpswlgkccwxirfwnruapp")) {
int wscnyk;
for (wscnyk=63; wscnyk > 0; wscnyk--) {
continue;
} 
}
return false;
}

bool etkrqny::nqoteydvedneauq(int zcbdpeemociy, bool aewzavm, double ecjgd, double dywsiuwlquxki, double qlnfgso, double ttdhngbvij) {
double kftesbswvndf = 19352;
string bzqot = "tbogteypdhnytcvtqnfpkabrogdohgfnuuiliijaurhlsnigdfbesdkjlmsyugfflrylbamsanvws";
string xuferzd = "jbglkqkx";
double inqzncocwvxfflt = 63001;
double aqxplgz = 47311;
double fvprsyfmx = 10209;
bool amqienqanal = false;
string hnprzfa = "exluqjxxrfperiwqsrjgctdmvgmyetkpsdrcebjyuflygmuvdqsbxsmqpdnpcqmnlcxijfjuoksp";
double lrfbdrmgtjym = 12886;
bool adqhkxtycmoizx = true;
if (10209 == 10209) {
int msnmhcxpq;
for (msnmhcxpq=87; msnmhcxpq > 0; msnmhcxpq--) {
continue;
} 
}
if (12886 == 12886) {
int rumash;
for (rumash=1; rumash > 0; rumash--) {
continue;
} 
}
if (string("exluqjxxrfperiwqsrjgctdmvgmyetkpsdrcebjyuflygmuvdqsbxsmqpdnpcqmnlcxijfjuoksp") == string("exluqjxxrfperiwqsrjgctdmvgmyetkpsdrcebjyuflygmuvdqsbxsmqpdnpcqmnlcxijfjuoksp")) {
int xtisykjnd;
for (xtisykjnd=2; xtisykjnd > 0; xtisykjnd--) {
continue;
} 
}
if (47311 != 47311) {
int btwdavgx;
for (btwdavgx=92; btwdavgx > 0; btwdavgx--) {
continue;
} 
}
if (63001 == 63001) {
int ydqkzlcifp;
for (ydqkzlcifp=76; ydqkzlcifp > 0; ydqkzlcifp--) {
continue;
} 
}
return true;
}

bool etkrqny::cqkbnfnjsauzgpxrfceqoj() {
bool mdvicthywgkhyz = false;
double huweygyqdp = 7223;
string iftswaccohswfyy = "nwspozcsfjeremsdnqzgycngawqkluprrcnnqcgembnrpbhrrnplztrsubfgrvqxm";
double ppiggimfmtq = 5318;
bool bxteoicqmycesw = true;
double gjcmvgdm = 2722;
bool rglszrureukdkpt = true;
int idspgihbrrlijm = 6448;
int bzpyphktcapxj = 1171;
if (1171 == 1171) {
int lud;
for (lud=54; lud > 0; lud--) {
continue;
} 
}
if (false != false) {
int wwwug;
for (wwwug=59; wwwug > 0; wwwug--) {
continue;
} 
}
if (2722 != 2722) {
int xekglkldef;
for (xekglkldef=27; xekglkldef > 0; xekglkldef--) {
continue;
} 
}
if (2722 != 2722) {
int mbkknywbvx;
for (mbkknywbvx=43; mbkknywbvx > 0; mbkknywbvx--) {
continue;
} 
}
if (false == false) {
int rzmnguquut;
for (rzmnguquut=87; rzmnguquut > 0; rzmnguquut--) {
continue;
} 
}
return true;
}

string etkrqny::tmrfvimzmrj(bool jooojcscge, bool lgghlset, bool rszwvmlteuohll) {
string jqrmqvnl = "etuoafq";
int zmqnkcfky = 4060;
double tfssxowto = 17774;
double lwmezck = 5357;
double enxqmvqrdo = 16201;
double mekyusn = 3385;
int megezzeianhzclb = 4734;
bool urtpgyjymb = true;
bool dkegxsixvlgn = true;
double nkofutozimi = 60489;
if (17774 != 17774) {
int pgd;
for (pgd=80; pgd > 0; pgd--) {
continue;
} 
}
return string("eciystqyhuknohghv");
}

void etkrqny::jrwxemcnkuavsdopqelaaer(bool dljpferonwy, string lmgpwobutq, bool ltwijjxuey, int yawgfhwowr, string scbyb, double rhheq) {
int wjmazld = 2681;
double fzaotfcrwkynjgc = 20883;
int fjipoiaksifm = 5949;
if (5949 == 5949) {
int smjh;
for (smjh=52; smjh > 0; smjh--) {
continue;
} 
}
if (20883 != 20883) {
int rylsnkc;
for (rylsnkc=61; rylsnkc > 0; rylsnkc--) {
continue;
} 
}
if (5949 != 5949) {
int weqivg;
for (weqivg=21; weqivg > 0; weqivg--) {
continue;
} 
}
if (20883 != 20883) {
int gutwxav;
for (gutwxav=72; gutwxav > 0; gutwxav--) {
continue;
} 
}
if (5949 == 5949) {
int zcdufvw;
for (zcdufvw=39; zcdufvw > 0; zcdufvw--) {
continue;
} 
}

}

etkrqny::etkrqny() {
this->tmrfvimzmrj(false, true, true);
this->jrwxemcnkuavsdopqelaaer(true, string("thjdhmju"), false, 1313, string("ftazoozrwydncmkhbabkftta"), 23182);
this->jollveejcsvlzcfkoxbhtptiu(7649, true, string("mmghiujxeyrkxsjitrqvwpgfshrefrtefsieqwotqmlckjvhnimxovospcpwqkjwrnpjjfctumfxvtujgqhucjbipvtivczxeb"), 2933, string("irspzowdgfgupajmtgwszfngelhhlydtipmmayrtwpjkytycxduwylzkmvejpsizkslamnewccpvqwmvhelgdihy"), 3531);
this->xpxdvyvaxftnoz(1202, string("zewkedinxivmsczewcpxkizspyiwrseqrsmuc"), 29132, 242, 952, 8822, false, 527, 2206, 40365);
this->oyspvxgxppncxlsynktrxi(string("ezgjxdonqogwezpd"), string("trjhmpwkfvgyxenynaqnwsoigwfsbvjbzicxvgraldvve"), false, 58695, 14167, 20444, 1101, true, false, true);
this->fcbptlyfdxtcuj(600);
this->nqoteydvedneauq(3750, false, 15885, 34183, 46326, 34236);
this->cqkbnfnjsauzgpxrfceqoj();
this->zjmigatcbuiqnhjwcahwi(string("amumiyvfiycleyzpqekdtclfkmxkrwu"), 23346, 8569, false, 36737, string("fpcrkupxcbtsjidwznggbmhvfidbyosczeelsaasfqkdhygtvkiilacmzwrel"), 38137, string("gdzelpycrsjkzlilbpcjyyccgficdntoitotqerxgeievkrkcvwdtayeugzgyrzbwouaguezvjgfiposfxqb"), 3936);
this->ueqnjmxfcwh(string("ybvekwlmoqqteohvxmcdupzgmidpkoayhbgzytacuambgeanytddejnevueliqfpzswy"), 6756, string("tbzqcmyixblhlzjtasnsjuhzlnjbdgpmdwydamglshfhwjawazlbfczwdjshfrfhnyschp"), 2672, 578, string("kguuvuuosrhpceemmjldmfwwsmlmxytbpkgbtagdtnmmrjsbroxwllmychfdmeycipkfllfbqauduxbnjycekgbchurssmvm"), true, false);
this->bchfuhbtzig();
this->ajifzdslupww(true, false, 14958, 4573, 1197, 4415, 1551, 2810);
this->abhrpsmgjioolnmo(string("zemklrkrnkonlfnzrxracwtiwcfrrgzzphbacehxugpvyeceiaxkzccfpnwdllyecoovxbmxbxqfzv"), string("mxjnxqbyzdvkkilgcdbkmflszjhxdihsptryixydqqdgrcqclueevvdzcjxasafqvdnfwoaelyvhuyvscrxybtkfwqtdhtfszg"), string("hzlmetxwxreyxpykxazpdgchsaszoposxsuvrxdbpqjcqccdcasubkjqcwztwwzrybjss"), string("wsebczd"), false, string("gvdfyqxeucsqvztwpxswmqswjazvs"), string("qoeudvglxjcubgrkowwjoifufzlnqklblheaqeooogpnreonvpscwmddnnagqotccosouian"));
this->sofceinfdesplx(20619, 1245, false);
this->gihptrhmwulfubli(string("goqteuusqbc"), 22948, string("mkesknyksmhopwlvomqeelqihpnlyyumadsvebnehappbhrlajmmsyoaev"), string("zmyvcryybhssry"), false, false, 46058, 563, 2486, false);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class pdgkjbc {
public:
int bnxfguztxiiqqd;
int kplgsguavnggcin;
double sflqww;
string vlufq;
double hggbjoclkhmnlxm;
pdgkjbc();
string fjgauyluzbewsacj(int zdguavpisq);
void gpzjqqaicdxrsfgthlyt(int tbmenqtku, int zwpsrcvfrzwe, string enydbrvexcnm, bool plvmk, bool mrqppocuezq, bool ktzrewyd, double xtnkxomko, int gqrpu, bool hvivym, string xzcbqtqyorp);
double ohzjovlgagtxuyp(bool oefiioeyygyh, double trziafrep, int vdsvrtlmpvd, int smhflpiryxyrfr, double eqtngysomces, bool xmzzcb);
int wzqodfwioltcpbuzg(double ftttynluwqyx, bool lvwcdepoexzsqu, bool kvbygxxjefd, double jrbqbxogtkcma);
int qgzzwegngmvtyqlaxv(int klbrhslq, bool cxqucdmjekibiv, int hscuvbbadwb, bool ygkwfioll, bool ywalwlvzuuytmzc);

protected:
double sclee;
string apqof;

bool qwolloqbkfchsvlxgvdfwlf(double bkeprtiemkfsz, double ehefcoypnadsk, string vogyeqojc, string ocdkpk, int kamhnxusxojyoqa, string uerqwtgaw, string aayjooa, bool frsmgxq);
string pgbvjgooeaegniebeooxnh(double mldglwogaizrex, string nwlsmgigrzx, string bxbuj);
bool gcobqhvpuer(double fpbte, string xpnfwygtbpsk, double ktltzsh, string zvqgypprzppq, bool lfsymwhyzpkdny, string failnarsh, string cewyrklyxygi);
bool gkdncarwpq();
int znipmjyhnncsvzubodzonu(int sbjhelegrmckwh, double vedtpn, string mfmehv, int nsulckdjegxci);
bool weekjmgxtfidgvhpz(int kwgjp, int zukxuidosluuijd, string pdzpxc, int xjokytheer, bool dseflk, int qklwjzbyo, string qxmnulyrpg, double sbnqrw);
bool zppjdixabmefjks(bool qglcv, bool bmoazdfxobfhko, bool stvtiwohckrjwgi, string egalofcvwvgws, double xkzweimakgysu);
int eiribtzmmlvsxrznso(int pqyijwjbgzi, int fblfxqyhkj, double cgicxtrvfk, int tjiqosgohvici, string cvdxntsvg, int timppkgrfqhck);
int uwdgfeuuvkcgntgbia(int nzxrpbuhohegi, bool sfhhurbpkc, bool ofncmbwaowsqr, int umitismjw, int omopt, bool gwpruiu, string qtopazhbmrfcqvq, bool xrixednd, bool pmcihcqgfl, int gvqobzr);

private:
int cdelhejjabysm;
string pknxyrib;
bool vujdbjijxylcco;

int khkpdefcggdbuvybrpnuuf(int dptof);
string cunelyvjzd(string bpuxa);
bool swsxswskwb(string eluay, bool gvusssf, double sagslbftfhftx, double lrjyb);
int mppjblgtefnyvecyth(bool jxbkxjonqy, double tjwetl, double kzgla);
void hfsalwgiynktju(bool xqzsompbquedzof, double jfjqub, string qxshdshdnut);

};




int pdgkjbc::khkpdefcggdbuvybrpnuuf(int dptof) {
return 58639;
}

string pdgkjbc::cunelyvjzd(string bpuxa) {
int vevruxx = 4102;
double bfsrralnqpqku = 3187;
int cvvqzfrr = 292;
bool hhtjwqloab = true;
double qvvfmzcxksrpuy = 24791;
bool nigfkixywugpz = false;
string zngktszegghjg = "javsirfznonpcjndcpzmlmlhfxysaavyphptashhtfpmerhkpydssttnpvbhmcqghussedlvfchrtg";
double tcgqobnjtfapq = 12854;
if (12854 == 12854) {
int kvzfz;
for (kvzfz=56; kvzfz > 0; kvzfz--) {
continue;
} 
}
if (3187 != 3187) {
int gmtdhlnj;
for (gmtdhlnj=18; gmtdhlnj > 0; gmtdhlnj--) {
continue;
} 
}
if (string("javsirfznonpcjndcpzmlmlhfxysaavyphptashhtfpmerhkpydssttnpvbhmcqghussedlvfchrtg") != string("javsirfznonpcjndcpzmlmlhfxysaavyphptashhtfpmerhkpydssttnpvbhmcqghussedlvfchrtg")) {
int wwwbwpk;
for (wwwbwpk=52; wwwbwpk > 0; wwwbwpk--) {
continue;
} 
}
if (12854 == 12854) {
int ohi;
for (ohi=66; ohi > 0; ohi--) {
continue;
} 
}
if (12854 != 12854) {
int oxirg;
for (oxirg=3; oxirg > 0; oxirg--) {
continue;
} 
}
return string("xbctipbefeoisyguny");
}

bool pdgkjbc::swsxswskwb(string eluay, bool gvusssf, double sagslbftfhftx, double lrjyb) {
double coftmkbiykyi = 34872;
bool axmha = true;
bool bwuupumvus = true;
if (true != true) {
int wmgl;
for (wmgl=42; wmgl > 0; wmgl--) {
continue;
} 
}
if (34872 != 34872) {
int xmbemdwwqz;
for (xmbemdwwqz=13; xmbemdwwqz > 0; xmbemdwwqz--) {
continue;
} 
}
if (true == true) {
int bvy;
for (bvy=64; bvy > 0; bvy--) {
continue;
} 
}
if (true == true) {
int wuotokd;
for (wuotokd=30; wuotokd > 0; wuotokd--) {
continue;
} 
}
if (true == true) {
int odxbl;
for (odxbl=67; odxbl > 0; odxbl--) {
continue;
} 
}
return true;
}

int pdgkjbc::mppjblgtefnyvecyth(bool jxbkxjonqy, double tjwetl, double kzgla) {
int jcwptvuociay = 65;
string wpdtahujwdld = "rmmharswpnmyxusdkfilffnbxbrqpienbokfcdeqim";
int ubsbgvdxwxgu = 3124;
string gfeemvi = "uxnulwyocmwewvsrifcgbtktnzdasfloltcdjdmfvlvopvztlsrgpvwgqaitybquscxldlwaujxvvaxxogtpkoqmya";
bool krvhdvtbhvq = false;
string pvkhtpm = "fxtrvojbnqsyjguctlaxkdbrmwpytkdiorldlqahufmiedrkedjhkfwceqfkkctgccldbvmlqedhoqzudl";
int pbcslgkfd = 49;
double ygkokhykphb = 61515;
double eamamnpjijj = 52871;
if (61515 != 61515) {
int ruosan;
for (ruosan=71; ruosan > 0; ruosan--) {
continue;
} 
}
if (string("fxtrvojbnqsyjguctlaxkdbrmwpytkdiorldlqahufmiedrkedjhkfwceqfkkctgccldbvmlqedhoqzudl") != string("fxtrvojbnqsyjguctlaxkdbrmwpytkdiorldlqahufmiedrkedjhkfwceqfkkctgccldbvmlqedhoqzudl")) {
int dafup;
for (dafup=30; dafup > 0; dafup--) {
continue;
} 
}
return 12440;
}

void pdgkjbc::hfsalwgiynktju(bool xqzsompbquedzof, double jfjqub, string qxshdshdnut) {
int dwxfjxdigs = 2064;
int jmcajizgrlnt = 274;
string nrbkajp = "oizzqtcvksbldxoaleupm";
if (274 != 274) {
int dgjyt;
for (dgjyt=86; dgjyt > 0; dgjyt--) {
continue;
} 
}
if (2064 == 2064) {
int tyast;
for (tyast=45; tyast > 0; tyast--) {
continue;
} 
}
if (274 != 274) {
int zzxmg;
for (zzxmg=97; zzxmg > 0; zzxmg--) {
continue;
} 
}

}

bool pdgkjbc::qwolloqbkfchsvlxgvdfwlf(double bkeprtiemkfsz, double ehefcoypnadsk, string vogyeqojc, string ocdkpk, int kamhnxusxojyoqa, string uerqwtgaw, string aayjooa, bool frsmgxq) {
bool kntkwjzvtat = true;
string onmjkb = "dvsxdxtemootbtlnmpyutazjfpxyn";
string aechprdhc = "fifsnpqhpfbwgvtvnkydxteaduhgcovnthcksszttfxkpuqjltuqouxzgmqycupathfdlsewthljuuwmr";
int rfdqtssyiyiwgel = 2342;
double cjgoseojs = 47532;
int xiylk = 2109;
string fohad = "adobkkaojiafuprqacstmmnteoduakezowlxvhotwerwtglqbiiyvqdzpewxqecitvbxjvbfot";
int asoykfoeyenuba = 3297;
string bonzemrk = "ubxyfldvwqvldzcnpireyvawccjnrwcnqwnlxspbdvkayzyjwgkuawxaduzbmhekrgecx";
bool knbihhbrapbccf = false;
if (47532 != 47532) {
int ckapktloy;
for (ckapktloy=4; ckapktloy > 0; ckapktloy--) {
continue;
} 
}
if (true != true) {
int fjok;
for (fjok=14; fjok > 0; fjok--) {
continue;
} 
}
if (false == false) {
int rppf;
for (rppf=8; rppf > 0; rppf--) {
continue;
} 
}
if (2342 != 2342) {
int cakoniw;
for (cakoniw=91; cakoniw > 0; cakoniw--) {
continue;
} 
}
if (false != false) {
int ecatcatdq;
for (ecatcatdq=28; ecatcatdq > 0; ecatcatdq--) {
continue;
} 
}
return false;
}

string pdgkjbc::pgbvjgooeaegniebeooxnh(double mldglwogaizrex, string nwlsmgigrzx, string bxbuj) {
string gefqpkaazsm = "efqbzrntkfntsexvqlzydiklltndguatoclcvdbggszhkfdwheyvllgopbo";
int jfdckeijrju = 400;
double lllquaqzcgf = 4174;
double dbauvnsg = 45393;
int filhxuo = 1426;
if (400 != 400) {
int aursbzpj;
for (aursbzpj=81; aursbzpj > 0; aursbzpj--) {
continue;
} 
}
if (4174 != 4174) {
int gdvoyvgrk;
for (gdvoyvgrk=13; gdvoyvgrk > 0; gdvoyvgrk--) {
continue;
} 
}
return string("dkpwfrpslhfzscyyezkr");
}

bool pdgkjbc::gcobqhvpuer(double fpbte, string xpnfwygtbpsk, double ktltzsh, string zvqgypprzppq, bool lfsymwhyzpkdny, string failnarsh, string cewyrklyxygi) {
string udtwsypvv = "fywmx";
int jhgfivsjty = 1712;
double cgfyinhgfhtwync = 8231;
if (string("fywmx") != string("fywmx")) {
int sjmdykqdd;
for (sjmdykqdd=6; sjmdykqdd > 0; sjmdykqdd--) {
continue;
} 
}
if (string("fywmx") == string("fywmx")) {
int aji;
for (aji=16; aji > 0; aji--) {
continue;
} 
}
if (1712 == 1712) {
int vd;
for (vd=43; vd > 0; vd--) {
continue;
} 
}
if (string("fywmx") != string("fywmx")) {
int odc;
for (odc=9; odc > 0; odc--) {
continue;
} 
}
return true;
}

bool pdgkjbc::gkdncarwpq() {
return false;
}

int pdgkjbc::znipmjyhnncsvzubodzonu(int sbjhelegrmckwh, double vedtpn, string mfmehv, int nsulckdjegxci) {
int snrdh = 2452;
double rwzgdahtaxv = 44464;
int blkxtp = 8461;
if (8461 != 8461) {
int orhfockln;
for (orhfockln=54; orhfockln > 0; orhfockln--) {
continue;
} 
}
if (2452 != 2452) {
int dceio;
for (dceio=10; dceio > 0; dceio--) {
continue;
} 
}
if (44464 != 44464) {
int gdipnbaww;
for (gdipnbaww=45; gdipnbaww > 0; gdipnbaww--) {
continue;
} 
}
if (2452 == 2452) {
int jtrtsoyap;
for (jtrtsoyap=44; jtrtsoyap > 0; jtrtsoyap--) {
continue;
} 
}
if (44464 == 44464) {
int ejfb;
for (ejfb=71; ejfb > 0; ejfb--) {
continue;
} 
}
return 23116;
}

bool pdgkjbc::weekjmgxtfidgvhpz(int kwgjp, int zukxuidosluuijd, string pdzpxc, int xjokytheer, bool dseflk, int qklwjzbyo, string qxmnulyrpg, double sbnqrw) {
double jdricjsiba = 24084;
bool rtdock = false;
double oanstizk = 65652;
int wuanjje = 209;
string uqdfakmglrrzc = "fxriutbmlbcfwlsjcnwxoyztozliigzvjo";
int qomiolsfk = 212;
if (212 != 212) {
int yzyzng;
for (yzyzng=66; yzyzng > 0; yzyzng--) {
continue;
} 
}
return false;
}

bool pdgkjbc::zppjdixabmefjks(bool qglcv, bool bmoazdfxobfhko, bool stvtiwohckrjwgi, string egalofcvwvgws, double xkzweimakgysu) {
bool jbxflytqjsdpfp = false;
double qmxovqjepmikdu = 7824;
double bjccgwxqv = 7718;
double lhiucehxvvfdnx = 18122;
string jcugghabhmoygq = "fbeimkhzpcitfktwzubxlwtmd";
if (false == false) {
int fuhzm;
for (fuhzm=91; fuhzm > 0; fuhzm--) {
continue;
} 
}
if (7824 != 7824) {
int crjqt;
for (crjqt=67; crjqt > 0; crjqt--) {
continue;
} 
}
return true;
}

int pdgkjbc::eiribtzmmlvsxrznso(int pqyijwjbgzi, int fblfxqyhkj, double cgicxtrvfk, int tjiqosgohvici, string cvdxntsvg, int timppkgrfqhck) {
bool ijsab = true;
double romcznvu = 35374;
bool cejsvwmtl = true;
string ndnejzpve = "nmworigujlhpgrwmitezoljhahqapzocqqvoumraj";
bool osordvcthztg = false;
string ubxphaqahgjbwql = "pmpwumhawlblkzjnrirvvqndiu";
string qhtvpsxzshs = "ehmjppsczbapqvffnjvgjnzkaxsftpfpbclmvracuvuejqtpwyuxlynvqjhbqeiqwhtjutihgfvzikgldmfsinltv";
string jztcjuzwofdkio = "fqqtrmjclzextuqttgmpibqevksspsnecbjxivxxlatclobxmzgrlysawvzzrxlvbuqsbymlvlmavpyoktoquyki";
if (true == true) {
int mvicl;
for (mvicl=83; mvicl > 0; mvicl--) {
continue;
} 
}
if (string("ehmjppsczbapqvffnjvgjnzkaxsftpfpbclmvracuvuejqtpwyuxlynvqjhbqeiqwhtjutihgfvzikgldmfsinltv") != string("ehmjppsczbapqvffnjvgjnzkaxsftpfpbclmvracuvuejqtpwyuxlynvqjhbqeiqwhtjutihgfvzikgldmfsinltv")) {
int cbkqia;
for (cbkqia=100; cbkqia > 0; cbkqia--) {
continue;
} 
}
if (string("nmworigujlhpgrwmitezoljhahqapzocqqvoumraj") == string("nmworigujlhpgrwmitezoljhahqapzocqqvoumraj")) {
int dou;
for (dou=55; dou > 0; dou--) {
continue;
} 
}
return 79664;
}

int pdgkjbc::uwdgfeuuvkcgntgbia(int nzxrpbuhohegi, bool sfhhurbpkc, bool ofncmbwaowsqr, int umitismjw, int omopt, bool gwpruiu, string qtopazhbmrfcqvq, bool xrixednd, bool pmcihcqgfl, int gvqobzr) {
double ypcpjlefxb = 35422;
int zkqfmcgcpco = 1335;
double dznpz = 40738;
double yfovafuuxs = 18562;
int jpuvfkbdvdsb = 1722;
bool sknvovvgdadxdgx = true;
double qjddfxbd = 20145;
if (40738 == 40738) {
int ahgt;
for (ahgt=37; ahgt > 0; ahgt--) {
continue;
} 
}
if (18562 == 18562) {
int ebau;
for (ebau=89; ebau > 0; ebau--) {
continue;
} 
}
if (35422 == 35422) {
int ua;
for (ua=91; ua > 0; ua--) {
continue;
} 
}
return 46582;
}

string pdgkjbc::fjgauyluzbewsacj(int zdguavpisq) {
int aiqqmcqowlxwfc = 682;
bool uggtelsm = true;
double avblxxyldxxza = 17274;
double sutsua = 8262;
return string("");
}

void pdgkjbc::gpzjqqaicdxrsfgthlyt(int tbmenqtku, int zwpsrcvfrzwe, string enydbrvexcnm, bool plvmk, bool mrqppocuezq, bool ktzrewyd, double xtnkxomko, int gqrpu, bool hvivym, string xzcbqtqyorp) {
int wrryx = 798;
string xiqbpei = "swvrgfrzpvricpwhvqcfrszpvorrydhksuhsytidx";

}

double pdgkjbc::ohzjovlgagtxuyp(bool oefiioeyygyh, double trziafrep, int vdsvrtlmpvd, int smhflpiryxyrfr, double eqtngysomces, bool xmzzcb) {
bool qboimzlrjblwb = false;
int ohmytrwexflxjkl = 1926;
string avgooeroxf = "sxrjvizhepjjehancpxzzwdvf";
return 35305;
}

int pdgkjbc::wzqodfwioltcpbuzg(double ftttynluwqyx, bool lvwcdepoexzsqu, bool kvbygxxjefd, double jrbqbxogtkcma) {
double ouzjrktssy = 4372;
string dplyyeahnwlvgmg = "jbqtxtmeejppvllfksjismssigpxuvfinerbsdtopxmgrmmbzkfxwzmgvobtmpqfpgi";
if (string("jbqtxtmeejppvllfksjismssigpxuvfinerbsdtopxmgrmmbzkfxwzmgvobtmpqfpgi") == string("jbqtxtmeejppvllfksjismssigpxuvfinerbsdtopxmgrmmbzkfxwzmgvobtmpqfpgi")) {
int rzbweolxqc;
for (rzbweolxqc=17; rzbweolxqc > 0; rzbweolxqc--) {
continue;
} 
}
return 72170;
}

int pdgkjbc::qgzzwegngmvtyqlaxv(int klbrhslq, bool cxqucdmjekibiv, int hscuvbbadwb, bool ygkwfioll, bool ywalwlvzuuytmzc) {
int wakhquxyfarklwz = 271;
bool zwzodsjzffupw = false;
double xyaatrihvakg = 18775;
int xmmezsnh = 1056;
string ktbwlhdkhs = "fzykkvhaguzyrmsaogykfbudkzxepznsbykzowiiykfilugjwafeq";
double rhenu = 58743;
if (271 != 271) {
int lzxhcfdx;
for (lzxhcfdx=36; lzxhcfdx > 0; lzxhcfdx--) {
continue;
} 
}
if (false == false) {
int pqhwaalue;
for (pqhwaalue=2; pqhwaalue > 0; pqhwaalue--) {
continue;
} 
}
if (271 == 271) {
int vljmr;
for (vljmr=36; vljmr > 0; vljmr--) {
continue;
} 
}
if (string("fzykkvhaguzyrmsaogykfbudkzxepznsbykzowiiykfilugjwafeq") == string("fzykkvhaguzyrmsaogykfbudkzxepznsbykzowiiykfilugjwafeq")) {
int kxaxdnkvu;
for (kxaxdnkvu=6; kxaxdnkvu > 0; kxaxdnkvu--) {
continue;
} 
}
return 24688;
}

pdgkjbc::pdgkjbc() {
this->fjgauyluzbewsacj(2843);
this->gpzjqqaicdxrsfgthlyt(1425, 1779, string("vhqxihtrvpknsxwfxzsiqmkzsivlcmwevaizippehezexegywbkyrmgcntngfpczefolyqcmaalafwkzgtlxalbxjhld"), false, false, true, 30213, 1414, false, string("ronapvwzwrqrhryjqcijaczxtdihhravwpvurqvbqlytxvdqicavzqix"));
this->ohzjovlgagtxuyp(false, 93832, 164, 360, 37084, true);
this->wzqodfwioltcpbuzg(13271, true, true, 4815);
this->qgzzwegngmvtyqlaxv(996, true, 1014, false, true);
this->qwolloqbkfchsvlxgvdfwlf(13058, 62874, string("ikvqaithsrcspskxtmuqjqocvakrtpneqfogjrsyttfximnhgewudnudiaiojvbeinekhqwtvgbpsqskiyrkugweumjekvfy"), string("uqwcvsjcn"), 3935, string("crhesayqnpfnpwbeqzngacrutejpgkqmrtriqebvh"), string("vpbpxhprxlhccbgoobmqdfynrwvqnbxfildkebbeksainatkejhhrikamjidawezocnaslceltnzpzpejcrteqyb"), true);
this->pgbvjgooeaegniebeooxnh(13286, string("avzwdfpmtayxilxndxkbvagwlukwwpwrozbtxcoocbdpseskjqgfzmyafxalxxgojpldawdn"), string("lmsmaqsplcllwgziuvslgpmbnbqcmzqjlg"));
this->gcobqhvpuer(28333, string("cksvuuib"), 9262, string(""), true, string("emsmuefrmqlnyqxdpzkqlrlyjkazpacqhnwkxvhhfgblbqdibp"), string("ilpmlsbvdlznnxmynzvtyglpopemrurbkpiui"));
this->gkdncarwpq();
this->znipmjyhnncsvzubodzonu(1407, 28259, string("prfwrswmpgywultfysznccxofkctzhbuhtai"), 4047);
this->weekjmgxtfidgvhpz(1353, 4153, string("xovanbatwkpvkaqhepjuhxfpmfkbvbnihtkebloifg"), 194, false, 2914, string("ppydtmjnsfzgrnndbupeskydaadaghhckkndjhnndjfeeqhtpvkxbokdudiplfrnrpgrltqobugrigkgpln"), 7026);
this->zppjdixabmefjks(false, false, true, string("leuvqdhejdwzllwctudltjivljixieagmyxstkjnfrhrttosotzfolinmsuvlzvmaakscgihurxotmgcuosdv"), 22537);
this->eiribtzmmlvsxrznso(2599, 1172, 31109, 8093, string("whpmmwksxrexsqyrsmkhsaqhzlfnalcxmrmqcyfqvdws"), 3122);
this->uwdgfeuuvkcgntgbia(2, true, false, 1353, 9426, true, string("ckdpbrsvpvfjvzlvthxyfitkfznyszlzchmksnmimbalxzewdwzpa"), true, true, 1078);
this->khkpdefcggdbuvybrpnuuf(67);
this->cunelyvjzd(string("qnbvniwqthaedknnknkrzubmmuoteasjmovxbacyd"));
this->swsxswskwb(string("uiqpsqjkbbcgftkzrceizkpxwzuashzrfcfkugqgminbkwrenxrvuvqordaejzxxbihacrmctffhqn"), false, 691, 31816);
this->mppjblgtefnyvecyth(true, 11466, 15921);
this->hfsalwgiynktju(true, 13065, string("fernmjqxokpqtdnuvktmcsdahqcnpwzmwvazkin"));
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class yjobzpt {
public:
string gvfysedlweyaatq;
int ckdthebuaofekz;
int krkwfdk;
double djkizbjtznq;
string idaxenv;
yjobzpt();
double olymloqngjlexzdf(string ggtycnyfejmipxa, bool vlxjegjqtayc, int rimmrf, string ptmitx, double twnalhdh, double eajknatyfnmcur, int gdlkzpwvwyxip, int qebkqargvdz, int vpyttwpe, double zxcbtdqb);
void kcpygprqvnjbtxhwwvi(bool csgjywfqxminiw, int podudkq, double mfwxbqqrzozim, bool zfjtekhtrb, double plcvttcuiwouf, int uikjqsklpglmjq, int xftqbipxmzefm, bool pkwjfsrethv, string pmaczunfglkrdr);
string cjcwbpzbby(string xrucskluyjypk);

protected:
int yvsnkjzgtkmkzo;
double hinhzzgqiln;
int xxlnwxhu;

string foqqvwktzyayaeyufjpiv(string wylesrnbrnrnre, int spmvmf, bool bdjlowi, string xhbdofzficfz, int xnbuffaz, bool mcbxtffms, string yaakxar);
string awkuzuboaltutchhkya();

private:
string jygilazhtybnvhh;
bool jlcifgisjmzndu;
double jzmslc;
double uptzeqrdi;

double xnkdnycgfwhrkv(string gadyzhhgaauzz, int cyuocprafvzo, bool nqzrdv, double yvjllxpqzstzxe);

};




double yjobzpt::xnkdnycgfwhrkv(string gadyzhhgaauzz, int cyuocprafvzo, bool nqzrdv, double yvjllxpqzstzxe) {
return 3651;
}

string yjobzpt::foqqvwktzyayaeyufjpiv(string wylesrnbrnrnre, int spmvmf, bool bdjlowi, string xhbdofzficfz, int xnbuffaz, bool mcbxtffms, string yaakxar) {
string rbmvpzxbrketpcl = "qrqvdw";
int rtqpfcjholr = 7301;
double ijymaleoso = 10034;
bool kiivuaetetbyo = true;
string jjlggqlj = "udbzxnnxe";
bool oaqtmxxvvstqq = true;
int ywhglsj = 3162;
string ejorxjnwiwmsb = "mkmgxcwpvks";
int rkurruskoswo = 4061;
if (string("qrqvdw") == string("qrqvdw")) {
int yrnqnqj;
for (yrnqnqj=47; yrnqnqj > 0; yrnqnqj--) {
continue;
} 
}
if (string("mkmgxcwpvks") == string("mkmgxcwpvks")) {
int xgpcfsw;
for (xgpcfsw=0; xgpcfsw > 0; xgpcfsw--) {
continue;
} 
}
if (3162 != 3162) {
int rdcikqrwm;
for (rdcikqrwm=35; rdcikqrwm > 0; rdcikqrwm--) {
continue;
} 
}
return string("phmbrfqieplniihqh");
}

string yjobzpt::awkuzuboaltutchhkya() {
string gkdbvow = "dxfqjstlhhikvdcgnlzlnqkayxrvipdwqcrdzvlqmjudqbal";
return string("eqanxoqrgdqrtmlbcd");
}

double yjobzpt::olymloqngjlexzdf(string ggtycnyfejmipxa, bool vlxjegjqtayc, int rimmrf, string ptmitx, double twnalhdh, double eajknatyfnmcur, int gdlkzpwvwyxip, int qebkqargvdz, int vpyttwpe, double zxcbtdqb) {
bool bwtbvgatbcwtn = true;
string hxyzn = "yzrqdyvdvminylvijmmammazqnibycgjbcggnsgjklzirmfseksclsketarvekcwtsngjgnrhquufohcnippuigp";
bool itnqxupebrjn = false;
int hkbdoocambqhd = 420;
double uqpjohzq = 3452;
int nrhkyfpzba = 4852;
double lhbfsdvtohawoz = 53256;
double uwmzzjronf = 24144;
double bkdsm = 17497;
int miixnfamjqrnigc = 4769;
if (24144 == 24144) {
int xmst;
for (xmst=17; xmst > 0; xmst--) {
continue;
} 
}
return 84544;
}

void yjobzpt::kcpygprqvnjbtxhwwvi(bool csgjywfqxminiw, int podudkq, double mfwxbqqrzozim, bool zfjtekhtrb, double plcvttcuiwouf, int uikjqsklpglmjq, int xftqbipxmzefm, bool pkwjfsrethv, string pmaczunfglkrdr) {
bool mlyqxflbpro = true;
double xlwqgxsfoy = 47076;
string xraqdhclpso = "prnxhlrnuwigvdlsbiutzsryfogzwiykykffcishjjuirxrgwaoysaqvvupgqlrspgixmmbkwkjhpwzsuzgpohlkrmgnprcmagot";
string kzshq = "hwbgcpefvmgyvbe";
if (true == true) {
int kryqwoug;
for (kryqwoug=35; kryqwoug > 0; kryqwoug--) {
continue;
} 
}
if (47076 != 47076) {
int ljkm;
for (ljkm=53; ljkm > 0; ljkm--) {
continue;
} 
}
if (string("hwbgcpefvmgyvbe") == string("hwbgcpefvmgyvbe")) {
int zfjurzsvq;
for (zfjurzsvq=70; zfjurzsvq > 0; zfjurzsvq--) {
continue;
} 
}
if (47076 != 47076) {
int qhb;
for (qhb=56; qhb > 0; qhb--) {
continue;
} 
}
if (string("prnxhlrnuwigvdlsbiutzsryfogzwiykykffcishjjuirxrgwaoysaqvvupgqlrspgixmmbkwkjhpwzsuzgpohlkrmgnprcmagot") == string("prnxhlrnuwigvdlsbiutzsryfogzwiykykffcishjjuirxrgwaoysaqvvupgqlrspgixmmbkwkjhpwzsuzgpohlkrmgnprcmagot")) {
int rhlykk;
for (rhlykk=81; rhlykk > 0; rhlykk--) {
continue;
} 
}

}

string yjobzpt::cjcwbpzbby(string xrucskluyjypk) {
string rcjemyvdgrzqam = "ckahinlrioghzsfuafilgeetbgpauwckao";
string gobknzqhwl = "heqlxwwbevrwbzghylosjpykhofjuhrilnigguwqeujgipqpf";
string eyisbtwek = "lfioctmekjuu";
bool xwsrqqye = true;
bool vttkb = false;
bool avcubpovoyrjzx = true;
int tmiaxsbr = 5150;
string uigzk = "f";
return string("ywmdqgteqahkplwgd");
}

yjobzpt::yjobzpt() {
this->olymloqngjlexzdf(string("aeryna"), true, 2105, string("tbmazgkxbelaoessubcrahkpbssjiwlaqamusuykukvsecghinlmjyqykcgnpcymjaopvwpyaihvwnmffmntuuvfswpjih"), 13460, 8586, 4140, 1768, 1195, 3714);
this->kcpygprqvnjbtxhwwvi(true, 2754, 64172, false, 38228, 1856, 5203, true, string("msoddkxbnezdytmbhpvuesjxaviezprnarqcyrjprtxbqlndtmfqqiahsyrsqvcicspkajjholgbzowbv"));
this->cjcwbpzbby(string("rlzfamlzmqjtwctauevwzpsnsydufjudknlgzgxudjmzcxksxodadrjcrprljlocitdvhnvvpnlvctfmrjhxpjapgibiilfpuh"));
this->foqqvwktzyayaeyufjpiv(string("ypygezgx"), 1039, false, string("gpffsuucrltaqwqmayntgyhvuovfhybedwscifxjlnpr"), 2055, false, string("vfhifddivkgtjfzpjlkn"));
this->awkuzuboaltutchhkya();
this->xnkdnycgfwhrkv(string("ezvcxnlxhgqeafikpydqlfwnmwftqqjifuneyonqolspgqcklkgzsqivrrxjmiciy"), 2286, false, 33556);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class teufrov {
public:
int rzzcmm;
bool gpnfbojtsa;
teufrov();
int gsgonqkmtqprevlewnudunii(int sgbquezjcnrru, double jvcaeykhnaqowz, bool btydtjzwttvyxkv, string zvabsognnknwq);
bool cbcwpkfpdxgk(bool uoiotwkyxir, string ydbymopgomdld, int qfvgmfcebfqxt, double vvzoygvvjkwrv);
int xnxzrtnhrusyszvaybuh(double wulffbwd);
double oeiivixlxrleashtkaaparbgm(bool hsisip, bool dqortzchgii, bool hnpamx, string rrgsksweucyt, int dmetq, string qyvqjdtbnoiv, string bnpumfjlorwd);
string owsoqdrxgdneycrqptejqezcq(string iddykhmvlvnvti, int potya, int sfwafqfpjmbhde, string einxj, int najkwezkkr, double ucksjlvzkrt, int jcbbzfwq);
double igrkftoslusyhnkcerbipbhc(string nwgaedl, double cfsdilegkdiazi, int jartdmagywt, bool aeytfyqttknozez, string szfbuahekxjqtq);
int bjdkymhddsvropcd(int iuwbtyjlh, int ixpijmccd, double dkeron, string sbmwzrjeu, int xsaxqtcbr, int mqcpmjakfdr, int wjizdnne);
string ryaikzpgtglg(bool uhtdzqmck, int crxyzjwcwfnuxp, int eflnlbrujwf);
string sbyrvgduwmkaxgzsfhoe(int bptgpwkvdpfjc, double svaxb, bool wpqmfbgskwnem, bool ofjdce);
string kzormwszbmcpyvsl(bool rrjkjrpp, bool tpyaemvgcjkwt, string bfwkjhwth, string xuummxjuezhfpz, string jxfmpbh, bool jfosyja);

protected:
bool ufpdlayelfwnfkg;
bool npynsnjztyvj;
string qyafqupkwv;

void ezqguzuviegaootu(string vmafjvevrj, bool gwlfjlexnnvefq, string uwpso, double mqaqgconpgmjrn, bool htathmef, double zjdothcaelmxed);
string znollsnvsuafiszyeqze(string julohcouyw, int ogvxgu, double kzqvfw, bool ipmmwpz, double pudsvwog, double omzwzmrhmo);
bool utybdsfjyqhc(double ygbzhisagbro, int fbcjk, double fjizsfmg, string ajgnhlaa, double ogsiafhltn, double dyldkcsy, bool frfemcoyotzjj, string yltkkohmuqeis, double kmzkcqzwpenwr, int jprlmifkdm);
double egezehwgpvbsrhrebjwmsonz(int xcrusdgl, int rebrpen, string qrdkhkut, bool kxuptfgixt, int kksdcmww);
double yqwvrldbmxeeuc(string wfiyfxtrgxxodg, bool jmqpeixvwcybjf, double cgiuqrllgx, int ggujbi, double lrowar, int zclccy, bool pizqnqeahkd, int bknenaml, string oezwollhjhnbcgt, int pxvywngldducxt);
bool pnttuvgbzhxkvwnxfvpxt(string xpjzvy, int bqththiheesi);
void hxmicrouxrgpawyvdboh(double jjphjggpsmauaw, double pjbkwjtgexydhf, bool ovmes, int zhvswlbbuhaw);
double nyxqgfnjgqa(string yagtxg, bool ibzwmquhxzphrhc, bool myhqsyafpg, string lidueuldmazhlai, bool sytofn, int uxjzpwloe, bool qajkrxosok, double fmtmjskzialu);
double dztdltupuvjxkqkhrahjd(string tzdlhqrxntwg, int njzrfhdfyc, string kbtshlkgbtxaavp);
int iqbbkgzvoapxqcdzhmbmxyp(int cehfv, string kxyesukxomux, double lmshotmgl, string opusqavjhpycyj, bool mxahdkmwb, double qbftreyuflrxaz);

private:
int rgvoha;
int cytvhomekptf;
int rzuqlhvchxxe;

void uhrczjuqojmpul(double lbpupaol, bool ojcbeh, int jfqpqpjdnt, int bkmpv, bool jkrxflif, string vkxucfmyjqenc, bool msjuhrb);
bool idaakeldzqgqypfo(int lujmsehakb, string alvsvdsvmg, double mcxiuhk, string fhcjhcy, int okysd, double gccjn);
string bsgrpimbxzmoztvafbzrr(double fqwgdzxhgy, bool jusmmsksdppfq, string hvqccw, double mevdajvs, int oraizdkahhdw, double hrlrhjvdbmpmf, bool hqkjqdrjg, string vumrbkwxlnwndt, bool yoqqceaiz, string jjllc);

};




void teufrov::uhrczjuqojmpul(double lbpupaol, bool ojcbeh, int jfqpqpjdnt, int bkmpv, bool jkrxflif, string vkxucfmyjqenc, bool msjuhrb) {
double bkckxgbqgbicw = 30766;
bool yxtcnr = false;
double ilrtvoxyjv = 64828;
int ewnacgzxahsx = 1003;
double ogmlw = 44559;
string kwhwffhf = "plpdjhkgaknshohcmpfqyxjvzvdcwendgppzjhyaoexoqjvmq";
if (64828 == 64828) {
int nayu;
for (nayu=25; nayu > 0; nayu--) {
continue;
} 
}
if (false == false) {
int fgpdwffi;
for (fgpdwffi=96; fgpdwffi > 0; fgpdwffi--) {
continue;
} 
}

}

bool teufrov::idaakeldzqgqypfo(int lujmsehakb, string alvsvdsvmg, double mcxiuhk, string fhcjhcy, int okysd, double gccjn) {
bool yayqxwgsumyjqqr = false;
bool pymnqgywgutvpn = false;
string ukvydo = "bkehoxmwlbzaibocxmmpwyswybtevirsjxdhgtds";
int vhoriqyyoqus = 802;
string nftyhjykyniuqwe = "q";
bool incbicbiwdkkgs = false;
int fbkudkfugclkx = 1810;
double tpcigmu = 14813;
if (false == false) {
int hriiqen;
for (hriiqen=20; hriiqen > 0; hriiqen--) {
continue;
} 
}
if (802 == 802) {
int jxrlymf;
for (jxrlymf=71; jxrlymf > 0; jxrlymf--) {
continue;
} 
}
if (string("q") != string("q")) {
int bwo;
for (bwo=62; bwo > 0; bwo--) {
continue;
} 
}
return true;
}

string teufrov::bsgrpimbxzmoztvafbzrr(double fqwgdzxhgy, bool jusmmsksdppfq, string hvqccw, double mevdajvs, int oraizdkahhdw, double hrlrhjvdbmpmf, bool hqkjqdrjg, string vumrbkwxlnwndt, bool yoqqceaiz, string jjllc) {
int rfhpgyxnrzeggm = 3237;
bool yjwoz = true;
int wttalhs = 5106;
int smxengflbqmn = 1877;
double lglyknhbnuy = 17979;
bool xdaso = false;
int iatcmfgjmymhre = 2143;
string ooffggyffai = "mufpefvjnpivgxdbxtmjxef";
bool xqyrt = false;
if (17979 != 17979) {
int plhdq;
for (plhdq=95; plhdq > 0; plhdq--) {
continue;
} 
}
if (false != false) {
int nm;
for (nm=87; nm > 0; nm--) {
continue;
} 
}
if (3237 == 3237) {
int dhyakabd;
for (dhyakabd=22; dhyakabd > 0; dhyakabd--) {
continue;
} 
}
return string("qavavat");
}

void teufrov::ezqguzuviegaootu(string vmafjvevrj, bool gwlfjlexnnvefq, string uwpso, double mqaqgconpgmjrn, bool htathmef, double zjdothcaelmxed) {
int epiekmvhopumk = 506;
bool qwuldrn = false;
bool jjpql = false;
double tgdkbfscmbvnn = 3826;
int ulgbjkpjhyrg = 2670;
int utdsalek = 1051;
double hzpfsaz = 20461;
if (3826 == 3826) {
int grdosmm;
for (grdosmm=10; grdosmm > 0; grdosmm--) {
continue;
} 
}
if (2670 != 2670) {
int khcttck;
for (khcttck=19; khcttck > 0; khcttck--) {
continue;
} 
}
if (3826 == 3826) {
int vqvxxu;
for (vqvxxu=36; vqvxxu > 0; vqvxxu--) {
continue;
} 
}
if (20461 == 20461) {
int wri;
for (wri=37; wri > 0; wri--) {
continue;
} 
}
if (3826 == 3826) {
int skyiu;
for (skyiu=71; skyiu > 0; skyiu--) {
continue;
} 
}

}

string teufrov::znollsnvsuafiszyeqze(string julohcouyw, int ogvxgu, double kzqvfw, bool ipmmwpz, double pudsvwog, double omzwzmrhmo) {
int ylhwdgustay = 7406;
if (7406 == 7406) {
int jmqqmpo;
for (jmqqmpo=65; jmqqmpo > 0; jmqqmpo--) {
continue;
} 
}
if (7406 == 7406) {
int unxssrxp;
for (unxssrxp=98; unxssrxp > 0; unxssrxp--) {
continue;
} 
}
if (7406 != 7406) {
int dvlypmmf;
for (dvlypmmf=49; dvlypmmf > 0; dvlypmmf--) {
continue;
} 
}
return string("obiygcqqjshzz");
}

bool teufrov::utybdsfjyqhc(double ygbzhisagbro, int fbcjk, double fjizsfmg, string ajgnhlaa, double ogsiafhltn, double dyldkcsy, bool frfemcoyotzjj, string yltkkohmuqeis, double kmzkcqzwpenwr, int jprlmifkdm) {
int nffthpvbq = 5782;
double bcvrgn = 56572;
double qcebkexbmcyy = 21334;
double rmcnvz = 36872;
bool ukfqqaricarlu = true;
int pteztnnpmppu = 4115;
string twtrmhguypknisz = "yxgcrkqvsupjgekiazvwjfhjnxehzmctbvitsbwy";
int bmjegbzo = 2532;
if (56572 == 56572) {
int gvvmh;
for (gvvmh=71; gvvmh > 0; gvvmh--) {
continue;
} 
}
if (36872 != 36872) {
int pamc;
for (pamc=63; pamc > 0; pamc--) {
continue;
} 
}
return false;
}

double teufrov::egezehwgpvbsrhrebjwmsonz(int xcrusdgl, int rebrpen, string qrdkhkut, bool kxuptfgixt, int kksdcmww) {
double krzjsbiyuutz = 5983;
double kmufmktyjeukt = 11942;
int gsnhynb = 2680;
double pluzjfxfsyrlo = 61678;
bool cpnkog = false;
double rudduehj = 12646;
if (2680 != 2680) {
int so;
for (so=48; so > 0; so--) {
continue;
} 
}
return 45074;
}

double teufrov::yqwvrldbmxeeuc(string wfiyfxtrgxxodg, bool jmqpeixvwcybjf, double cgiuqrllgx, int ggujbi, double lrowar, int zclccy, bool pizqnqeahkd, int bknenaml, string oezwollhjhnbcgt, int pxvywngldducxt) {
string dezhcfn = "sglfkiyjbxdgzhicnnjkftjpxzgljmjdbpvttdlsmgfjhrx";
bool cgwhpyeuzu = false;
int tpvkldzuko = 6311;
string lrxcdcft = "liiqjnvnwagphqhgzkitnnffnsntrybhy";
if (string("sglfkiyjbxdgzhicnnjkftjpxzgljmjdbpvttdlsmgfjhrx") != string("sglfkiyjbxdgzhicnnjkftjpxzgljmjdbpvttdlsmgfjhrx")) {
int iux;
for (iux=16; iux > 0; iux--) {
continue;
} 
}
if (string("sglfkiyjbxdgzhicnnjkftjpxzgljmjdbpvttdlsmgfjhrx") == string("sglfkiyjbxdgzhicnnjkftjpxzgljmjdbpvttdlsmgfjhrx")) {
int lfpgsgfhm;
for (lfpgsgfhm=61; lfpgsgfhm > 0; lfpgsgfhm--) {
continue;
} 
}
if (string("liiqjnvnwagphqhgzkitnnffnsntrybhy") != string("liiqjnvnwagphqhgzkitnnffnsntrybhy")) {
int dzpmxrxnjf;
for (dzpmxrxnjf=91; dzpmxrxnjf > 0; dzpmxrxnjf--) {
continue;
} 
}
if (false == false) {
int gstyrga;
for (gstyrga=41; gstyrga > 0; gstyrga--) {
continue;
} 
}
return 34061;
}

bool teufrov::pnttuvgbzhxkvwnxfvpxt(string xpjzvy, int bqththiheesi) {
bool szslfhm = false;
if (false != false) {
int ufkcqsq;
for (ufkcqsq=6; ufkcqsq > 0; ufkcqsq--) {
continue;
} 
}
return true;
}

void teufrov::hxmicrouxrgpawyvdboh(double jjphjggpsmauaw, double pjbkwjtgexydhf, bool ovmes, int zhvswlbbuhaw) {
int hojaoknwwougdb = 1144;
string keducdc = "razikarkhqwobhtietgdubz";
int cwksx = 744;
string uopecafqugnp = "zymyzqzkdwfswpsfkqvrnkpyyhniddchaj";
bool exqxyjsrwph = false;
int rtxzjnlmmf = 3822;
int fzygmsspemx = 2666;
double nkcdfkzdftgiwn = 26183;
int ynjovwhd = 2003;
if (false != false) {
int pydcsocqay;
for (pydcsocqay=33; pydcsocqay > 0; pydcsocqay--) {
continue;
} 
}

}

double teufrov::nyxqgfnjgqa(string yagtxg, bool ibzwmquhxzphrhc, bool myhqsyafpg, string lidueuldmazhlai, bool sytofn, int uxjzpwloe, bool qajkrxosok, double fmtmjskzialu) {
double iyutxjhaykbabrs = 31150;
string nvgsae = "omrv";
int dpqaapc = 370;
if (string("omrv") == string("omrv")) {
int vhqcw;
for (vhqcw=71; vhqcw > 0; vhqcw--) {
continue;
} 
}
if (370 != 370) {
int zcoqfirb;
for (zcoqfirb=25; zcoqfirb > 0; zcoqfirb--) {
continue;
} 
}
return 47747;
}

double teufrov::dztdltupuvjxkqkhrahjd(string tzdlhqrxntwg, int njzrfhdfyc, string kbtshlkgbtxaavp) {
int yfpspicepda = 1484;
if (1484 != 1484) {
int ioffvk;
for (ioffvk=65; ioffvk > 0; ioffvk--) {
continue;
} 
}
if (1484 != 1484) {
int juidwgdyuy;
for (juidwgdyuy=25; juidwgdyuy > 0; juidwgdyuy--) {
continue;
} 
}
if (1484 != 1484) {
int crvjjds;
for (crvjjds=100; crvjjds > 0; crvjjds--) {
continue;
} 
}
return 89132;
}

int teufrov::iqbbkgzvoapxqcdzhmbmxyp(int cehfv, string kxyesukxomux, double lmshotmgl, string opusqavjhpycyj, bool mxahdkmwb, double qbftreyuflrxaz) {
bool dntuyldhgjpr = false;
double ruffkpivry = 9916;
bool ovurrhcgiitxhdg = true;
double zblfcezjremegrn = 47867;
bool hxwcrsrxjmri = false;
bool axhokcxkoo = false;
string rfnfkhqtozlgtbq = "velayjtdzungjfybgyctghoqrlxnsgroydtypdzbdnatyzyhuyawfrcme";
if (47867 != 47867) {
int lmp;
for (lmp=84; lmp > 0; lmp--) {
continue;
} 
}
if (9916 == 9916) {
int fexmsshin;
for (fexmsshin=90; fexmsshin > 0; fexmsshin--) {
continue;
} 
}
return 90872;
}

int teufrov::gsgonqkmtqprevlewnudunii(int sgbquezjcnrru, double jvcaeykhnaqowz, bool btydtjzwttvyxkv, string zvabsognnknwq) {
string syrldmvdpdhzf = "pyrildkarvavthcbclrqojuhlwogxlnvbvwtozqbrdoonlwqfjjkcooanvqpgtzmfgnwyuxcnpskhthzfpflzimezxwwpjhvc";
bool fkiycyaegblrar = false;
int ityldhqw = 178;
string nniktpiptwuffa = "kppkfccjlblsg";
double zvoeyyzie = 19419;
string fhcdy = "rogdqycygelfltvzbshchindtowwoczkjho";
bool geyauvlh = false;
int mmtknreya = 2779;
return 93094;
}

bool teufrov::cbcwpkfpdxgk(bool uoiotwkyxir, string ydbymopgomdld, int qfvgmfcebfqxt, double vvzoygvvjkwrv) {
return true;
}

int teufrov::xnxzrtnhrusyszvaybuh(double wulffbwd) {
int ykuwxuml = 359;
bool ydmppajmvcwsdxa = true;
int kjyxaqxsbjq = 3462;
if (359 != 359) {
int afzw;
for (afzw=97; afzw > 0; afzw--) {
continue;
} 
}
if (true != true) {
int hlsn;
for (hlsn=29; hlsn > 0; hlsn--) {
continue;
} 
}
if (359 == 359) {
int ltmipek;
for (ltmipek=63; ltmipek > 0; ltmipek--) {
continue;
} 
}
if (3462 != 3462) {
int ivgyytssx;
for (ivgyytssx=49; ivgyytssx > 0; ivgyytssx--) {
continue;
} 
}
return 8610;
}

double teufrov::oeiivixlxrleashtkaaparbgm(bool hsisip, bool dqortzchgii, bool hnpamx, string rrgsksweucyt, int dmetq, string qyvqjdtbnoiv, string bnpumfjlorwd) {
int tqqkwwk = 2192;
int rqpywcnzuwyqu = 4437;
string kfntfavvejdxh = "vnctiiknpxcalifkcvlsrfzbltzblanqkhjszlbgfjjoxcwnmzfctfikmyfgyaqzddajgyrbdbugdsfigrlmncg";
bool lszwutxxwrsyfj = false;
int yenvaefjehamrl = 709;
int zwnidrkukquoohc = 907;
if (4437 == 4437) {
int jb;
for (jb=19; jb > 0; jb--) {
continue;
} 
}
return 99927;
}

string teufrov::owsoqdrxgdneycrqptejqezcq(string iddykhmvlvnvti, int potya, int sfwafqfpjmbhde, string einxj, int najkwezkkr, double ucksjlvzkrt, int jcbbzfwq) {
double hdugaslbvzoryf = 46329;
if (46329 == 46329) {
int stvbuwixn;
for (stvbuwixn=73; stvbuwixn > 0; stvbuwixn--) {
continue;
} 
}
if (46329 != 46329) {
int dkllnctdgg;
for (dkllnctdgg=20; dkllnctdgg > 0; dkllnctdgg--) {
continue;
} 
}
return string("vtmydb");
}

double teufrov::igrkftoslusyhnkcerbipbhc(string nwgaedl, double cfsdilegkdiazi, int jartdmagywt, bool aeytfyqttknozez, string szfbuahekxjqtq) {
bool lighallpkmya = false;
string dmmvgivxpyf = "zfaiqibhufbvo";
if (false != false) {
int xs;
for (xs=84; xs > 0; xs--) {
continue;
} 
}
if (string("zfaiqibhufbvo") != string("zfaiqibhufbvo")) {
int qvcd;
for (qvcd=86; qvcd > 0; qvcd--) {
continue;
} 
}
if (string("zfaiqibhufbvo") == string("zfaiqibhufbvo")) {
int lfiqiyxer;
for (lfiqiyxer=98; lfiqiyxer > 0; lfiqiyxer--) {
continue;
} 
}
if (string("zfaiqibhufbvo") != string("zfaiqibhufbvo")) {
int hi;
for (hi=22; hi > 0; hi--) {
continue;
} 
}
if (false == false) {
int ism;
for (ism=89; ism > 0; ism--) {
continue;
} 
}
return 77079;
}

int teufrov::bjdkymhddsvropcd(int iuwbtyjlh, int ixpijmccd, double dkeron, string sbmwzrjeu, int xsaxqtcbr, int mqcpmjakfdr, int wjizdnne) {
string iqzinhbrkoe = "rmmpuzpghtreghdvwxipynvrlezsdobibqaaqhpvticzxnczzousp";
double ztrngfclpmc = 46220;
bool kwdka = true;
double ihnxbddjx = 1464;
if (string("rmmpuzpghtreghdvwxipynvrlezsdobibqaaqhpvticzxnczzousp") != string("rmmpuzpghtreghdvwxipynvrlezsdobibqaaqhpvticzxnczzousp")) {
int pwzxxbxgba;
for (pwzxxbxgba=62; pwzxxbxgba > 0; pwzxxbxgba--) {
continue;
} 
}
if (46220 == 46220) {
int jklrpycd;
for (jklrpycd=76; jklrpycd > 0; jklrpycd--) {
continue;
} 
}
return 22819;
}

string teufrov::ryaikzpgtglg(bool uhtdzqmck, int crxyzjwcwfnuxp, int eflnlbrujwf) {
string pfiahmdctqbax = "mmovomgrnlkmgxbucfvizuvztmezrlqgnkksqhifeyuvbmrihnpfvofcos";
bool mdtikusolbhnrfl = true;
int yqzshcpa = 1147;
if (true != true) {
int vlntcdu;
for (vlntcdu=56; vlntcdu > 0; vlntcdu--) {
continue;
} 
}
if (1147 != 1147) {
int kwqj;
for (kwqj=26; kwqj > 0; kwqj--) {
continue;
} 
}
if (string("mmovomgrnlkmgxbucfvizuvztmezrlqgnkksqhifeyuvbmrihnpfvofcos") != string("mmovomgrnlkmgxbucfvizuvztmezrlqgnkksqhifeyuvbmrihnpfvofcos")) {
int pi;
for (pi=65; pi > 0; pi--) {
continue;
} 
}
if (string("mmovomgrnlkmgxbucfvizuvztmezrlqgnkksqhifeyuvbmrihnpfvofcos") == string("mmovomgrnlkmgxbucfvizuvztmezrlqgnkksqhifeyuvbmrihnpfvofcos")) {
int ofqxx;
for (ofqxx=60; ofqxx > 0; ofqxx--) {
continue;
} 
}
return string("yxzihsbzdltjivrngh");
}

string teufrov::sbyrvgduwmkaxgzsfhoe(int bptgpwkvdpfjc, double svaxb, bool wpqmfbgskwnem, bool ofjdce) {
int ynjdzcwmhfbaw = 7245;
int dbycihcyc = 96;
double tzrrqf = 40635;
bool jgrwvphmangzfv = false;
double aepfihwyo = 10118;
int dlckkeynup = 373;
return string("zrm");
}

string teufrov::kzormwszbmcpyvsl(bool rrjkjrpp, bool tpyaemvgcjkwt, string bfwkjhwth, string xuummxjuezhfpz, string jxfmpbh, bool jfosyja) {
string zmjgpmw = "jhyvfgyhzuzmlhehevutwb";
int sefvkdsopcjul = 5217;
string rhkryuxwqim = "mcbbraikgbqbcvyskuucwgrmkzlurlp";
bool bmrwo = false;
double zsddazddhjsem = 81764;
if (string("jhyvfgyhzuzmlhehevutwb") == string("jhyvfgyhzuzmlhehevutwb")) {
int vovonnooqv;
for (vovonnooqv=29; vovonnooqv > 0; vovonnooqv--) {
continue;
} 
}
if (false != false) {
int ambyvv;
for (ambyvv=45; ambyvv > 0; ambyvv--) {
continue;
} 
}
if (81764 == 81764) {
int aedrqtcm;
for (aedrqtcm=88; aedrqtcm > 0; aedrqtcm--) {
continue;
} 
}
if (string("mcbbraikgbqbcvyskuucwgrmkzlurlp") == string("mcbbraikgbqbcvyskuucwgrmkzlurlp")) {
int hb;
for (hb=16; hb > 0; hb--) {
continue;
} 
}
return string("pepwfxiz");
}

teufrov::teufrov() {
this->gsgonqkmtqprevlewnudunii(1302, 33214, true, string("iqbsagcgunkamwfgses"));
this->cbcwpkfpdxgk(true, string("hvihvtiixcaiezncbeuurrhdnduwq"), 6042, 6325);
this->xnxzrtnhrusyszvaybuh(69778);
this->oeiivixlxrleashtkaaparbgm(true, true, true, string("pshexpgpmapihbikwtxqouxacuguadcpfemodxoqae"), 3230, string("wxtgnfculodenegiztyfozwnshousakfpjtuhogtncsqkpplqznxsliopsgafgyiwqarnsdwcuncurovvfwfolcxoenucxqyebf"), string("mgpjvpyrkwrrofyniwaznbriiignnmmluldsbfcaykoaeqaqmvpkczwkrhcdygwrklhmmtunixe"));
this->owsoqdrxgdneycrqptejqezcq(string("snmzahgxkfbwuymdkcmpbaamprgxkpoaqjlmommucekzahkibhtrlrcukytgwvairlzxzashdpdjxrjcetjtknzkzngerc"), 3826, 1351, string("srhrxmpjfvvygioysfiqixuwqsobpninki"), 5573, 8966, 2030);
this->igrkftoslusyhnkcerbipbhc(string("xggqlogonypecibhqisxcoelsstrqljmdduhxefgj"), 5981, 5487, true, string("joliyitehweyuoumxtpkyfqmsaby"));
this->bjdkymhddsvropcd(3197, 3546, 19889, string("swwlspptpvgafhbiowrtrjnjczspyrydjsvocvtkyulceqz"), 1158, 296, 7000);
this->ryaikzpgtglg(true, 450, 2721);
this->sbyrvgduwmkaxgzsfhoe(2909, 50762, true, true);
this->kzormwszbmcpyvsl(true, true, string("goqqypytf"), string("qgjkfsbbtniknomsktneudvqorsitdiirnmbhhgpmxavlyxnezghbghzdm"), string("sqcknvybkiyfaxcrpudqagdtijrxhuasnarcykghgw"), true);
this->ezqguzuviegaootu(string("mdaryvsypbxwvcpoaxdjmlduuemwriuxmlvkkclkrliabqsmlmfddkszndarkhwuxg"), false, string("j"), 22041, true, 6367);
this->znollsnvsuafiszyeqze(string("bdksntlwurztvaqhmzgihovlsvjvuxomyrstmjvvwkbbmwzqqpkjybrxijnmttvmrdph"), 4079, 1083, false, 27974, 37281);
this->utybdsfjyqhc(3987, 1692, 62295, string("uzqlpujgiywrsimrvvanxjxvodfygmoedctbkjvvrehonrqz"), 16966, 56261, false, string("kbrnynlqrpqzgqrxabpxkeijzcxfkfwaincjzxeuafrphbzyvygnmwwqcselscmhcfmwhjozlabzsconql"), 48617, 3346);
this->egezehwgpvbsrhrebjwmsonz(840, 3368, string("dkoqnirghagpmbzzfezaplylmweeyqudjsmtmrlzvzygvxznrmnqfgnzykebyzunbamdccillhyaunovtrujhitbzirdzhpdjbnq"), false, 482);
this->yqwvrldbmxeeuc(string("mpiifbwizlgqjplydodptymi"), false, 10433, 193, 48353, 3832, true, 409, string("nicahlmuilxixbymbcza"), 4195);
this->pnttuvgbzhxkvwnxfvpxt(string("wkbrjuoeennvymfbkbtldpdnngqdibbjzcdwtmamwuhmmonkwtzjdrpgkhltbseathdyxzfxsyxlndshlvcmcfwrtbi"), 8373);
this->hxmicrouxrgpawyvdboh(721, 51955, false, 2036);
this->nyxqgfnjgqa(string("mrnmihdfzrcotwmnuxigrkmri"), false, false, string("zbvtltmvozutpcdgxzbcvf"), false, 220, false, 60851);
this->dztdltupuvjxkqkhrahjd(string("uqboacmmhwjbbqjpxqhhlmgyptsddqdssljkjfbmnqaktwcquozjcnwacgkiaaokfvoj"), 2425, string("khopeqwbtjabzildeomjwqvunsifinrpzoktziduclszdzhpev"));
this->iqbbkgzvoapxqcdzhmbmxyp(5280, string("paicgqfgrmnfmekhxkikrxwrupitsnotrzrewlakfzyuaqywhapggqllwmbkkpgtpyoijdqq"), 58670, string("ldwqxohucnaiuhb"), false, 62071);
this->uhrczjuqojmpul(6396, true, 891, 378, true, string("kuoehmbvnetwnpvnqkoumpylcowdzgjogxnulcpctuxulrhrjcwcrebacxkygbbqfbltckmavwhihsyvdxxfcmjeyyqj"), true);
this->idaakeldzqgqypfo(30, string("pgoupduihxjqydeqlvkddcbpotzliudocnsxauhedtbubnjbnt"), 7725, string("jpsururzqzjqlvtwquxbavrauyanducxhqbvzfzyjqmxxfpyzpepstedhimcnkfqckwbrcbvrdzmxgggvkmexye"), 2957, 425);
this->bsgrpimbxzmoztvafbzrr(5276, false, string("nvolrukjeanvy"), 73875, 8416, 69581, true, string("xgdopptpsqtgvjvtmzhgshbvwbtbydpxicazzaomwgkmtzstkplqvzejasjnggdkntaadxdgzmswhephbib"), false, string("uubwwmltidmnuydqqihqifdnyfewjoffclrbyffojzjujmufhvkimqthtvdskfwcphwqiddopvgtlphvkmb"));
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class giuosve {
public:
string fkeqbcvgzl;
double fecjooxnvwc;
bool kvixtciuwt;
giuosve();
void nfnkkvpnjyjmkgjnanqyl();
string lbsvuhmjuvlkcwhulujurwc(double zjkoiygk, double pfxpmcbpoq, string zfjhhril, double eerdxs, bool jgdsjawsivbxqwf);
string mcmbtjwobrfdmtyhejr(bool ravhyrdrgdj, int pdirxwafy, bool bwqdylggwvp, int mgryckfjeio, bool ayfkre, int onmzhcdrgvr, bool sneictvzodkc);
string wmtedvxxzdmetwukbs(string ufowkcdblw, int nuszqvuthhv, int mkbrlqburpux, double eaouh, bool efgaamzk, double smobvtmaac, double bygbsyayws, bool bhhhheveujzw, int bllpzdf, int wlslkhxushb);
double ronpkyrawjnelvmbnvg();
string xahrhlnmjwwixqabcmuax(string sajwlangpfpm, bool ssvywatcqiendof, bool zhvzmfjvwlqhm, int sxytjx, string tymlfvmxpmra, bool wkwdoqtabku);
int jimvsapgrmxvunuzuysu(int jxxgxeyylkxygk, bool afxvospzfcwnrp, double ushfgxyrw, int xorfdibg, string dkeoxquxc);
bool dpjmnidkee(int vjkqgurmqg, bool boyhbbrmaxm, double pykpvatvdqf);
string fmidksvwdoyrgd(string colqaxlnfsjawu, string ohtoaevk, string zhqotb, int odlfidehl, double azidwepzxzdgeda, double ultdq, int mbyfgg, bool tjcqbyxrbf, int nmombssbiej);
string uqfkbcqucdoujaqzpvgsjhkhk();

protected:
int tfxbcbjeeiuf;
bool xfgpmtiyrevk;
bool xrfqsy;
int iwvsrqraywmnvf;
double deyriuwpp;

void cvgoopjxzvwrtyvmcfnnzyi(int nzrdx, int vunxryxj, string uhdsrozxqiqw, string pubrkjxptldxz, bool ocjnjebg);
double stcvjrdvfebruxhfmixxcsazh(int gwberl, double giucmowwfsbqer, double cowqanatdi, int phqlbjohj, string olceqfwj);
bool tqpgtyhcvfakxucbdkd(bool yjbreb, int eqogmpwshhseb);
double azbgkropkedbpqhx(double rczvjjlbqlgzldz, int euaserz, double ccvfbkevlzrvjci, double npoxcgpls, double wfokjodxgnuc);
double aiqygmlnqrgwrjti(bool ftxrnpyuh, double usgydoog, bool pjxustqheccbpw, int zyvlnukwvxxwdcm, string kaowgkny, double dvaed, double xescusqrp);

private:
int omoudta;

double hrgoyoexnlmxrlnazcj(int ugcxfqoch, string tsddprdzercha, string mellcsir, double ntuuvnoogwug, string zhlhcv);
double joyybdvwnmdcuwf(string bwazamcxgjq, int winzuc, bool sscbcvpvhvmx, int nsoqczihg, string qwrxfvohozdbfuu, string nsnquwtgm, double vbxwykpcy, string zrqqrehvhu, string badqanm, bool hknbjoq);
bool fmsrewrcvq(string jhycedggmfisul);
void fkpauzmdayovzyiyvcmgyzl(int zkiqhsmuojnjf, bool xthzdge, double zkdmktszm, int xidqmbvq, int vhjjtbfn, double srvjvicwze);
double esvbweaclf(string omfslqsqmlsv, double zhdoaxus, bool cdimnuegqywoou, bool ugpleketxlyqcf, int sepnt);

};




double giuosve::hrgoyoexnlmxrlnazcj(int ugcxfqoch, string tsddprdzercha, string mellcsir, double ntuuvnoogwug, string zhlhcv) {
string bbrmtoetr = "seibwtaiyywjzsixgzyalfaxtebfisrzeexondpzuebnpvgvfl";
string ivpmc = "jgfrgaxmlmuvipcxdlapsgqqknim";
string mkkdbcblyqlplkw = "pnmw";
bool ijgtnrcbcl = true;
string ezxgkjwpxwk = "mqgeur";
string usbdvgntdirkg = "nbkjn";
double qkzziovu = 4778;
string gofjfjotpghfa = "cvohzvhgmlcctbijfitdtzhpsptptdiqpqkuvq";
string dkrhky = "arrrcvuxiykjkycwbzsrxwgzoonmwshrmeqgoyoatheorpjllsszqcenyxokqoewjcjapzvgxglckvymuuqugznhednzihdnq";
if (string("jgfrgaxmlmuvipcxdlapsgqqknim") != string("jgfrgaxmlmuvipcxdlapsgqqknim")) {
int otdrtxhstu;
for (otdrtxhstu=75; otdrtxhstu > 0; otdrtxhstu--) {
continue;
} 
}
return 20690;
}

double giuosve::joyybdvwnmdcuwf(string bwazamcxgjq, int winzuc, bool sscbcvpvhvmx, int nsoqczihg, string qwrxfvohozdbfuu, string nsnquwtgm, double vbxwykpcy, string zrqqrehvhu, string badqanm, bool hknbjoq) {
double qqfzvdcirskgdr = 47306;
double whmhofjmwk = 20631;
string quzxsihlfrx = "seiakcfkemcbdjakdpyxlufdztlbflthffrvobolxhrutxvjtuecurzazpriiqucic";
return 7581;
}

bool giuosve::fmsrewrcvq(string jhycedggmfisul) {
double fyepx = 36972;
int ncbsb = 533;
return true;
}

void giuosve::fkpauzmdayovzyiyvcmgyzl(int zkiqhsmuojnjf, bool xthzdge, double zkdmktszm, int xidqmbvq, int vhjjtbfn, double srvjvicwze) {
bool uobgpyyb = false;
bool khffqdtlpknqbos = true;
bool pvjwinvy = false;
string vbplnei = "gdgndxh";
double eqcudgkhabb = 50255;
double lmuetr = 23081;

}

double giuosve::esvbweaclf(string omfslqsqmlsv, double zhdoaxus, bool cdimnuegqywoou, bool ugpleketxlyqcf, int sepnt) {
int gloxpqrxebztxom = 2433;
int mnebzglryjufnf = 6486;
int kjjmnwzsuhpgoan = 2754;
bool forsuyendanpoau = true;
int rttca = 2242;
bool zfywgrk = true;
string gpflddkj = "saqfayegaodkslwefreankrrmlgpbqudsxhpogcbcniuuiiruufjovazeilhyvasjsadoepbrfgglervkyclsxk";
double vvaywxhwg = 10259;
bool ozcfmhhkyowb = false;
if (6486 == 6486) {
int vioqzl;
for (vioqzl=69; vioqzl > 0; vioqzl--) {
continue;
} 
}
if (true != true) {
int wfevtfbzn;
for (wfevtfbzn=0; wfevtfbzn > 0; wfevtfbzn--) {
continue;
} 
}
return 62400;
}

void giuosve::cvgoopjxzvwrtyvmcfnnzyi(int nzrdx, int vunxryxj, string uhdsrozxqiqw, string pubrkjxptldxz, bool ocjnjebg) {
int uzwoxlgyazaluu = 971;
bool caqqzmo = true;
if (971 == 971) {
int etquq;
for (etquq=28; etquq > 0; etquq--) {
continue;
} 
}

}

double giuosve::stcvjrdvfebruxhfmixxcsazh(int gwberl, double giucmowwfsbqer, double cowqanatdi, int phqlbjohj, string olceqfwj) {
bool khnzuqydcybtv = false;
bool hzchwkzu = false;
double hmakjdirajsnndx = 4827;
bool dftdjxqhqq = false;
string fpqyr = "nuygjruircmywfdxbuvbusxtgofkfsmsaoqahzzy";
if (false != false) {
int keltmsxd;
for (keltmsxd=76; keltmsxd > 0; keltmsxd--) {
continue;
} 
}
if (false != false) {
int ggq;
for (ggq=10; ggq > 0; ggq--) {
continue;
} 
}
return 66410;
}

bool giuosve::tqpgtyhcvfakxucbdkd(bool yjbreb, int eqogmpwshhseb) {
int ifiahbbxj = 2155;
return false;
}

double giuosve::azbgkropkedbpqhx(double rczvjjlbqlgzldz, int euaserz, double ccvfbkevlzrvjci, double npoxcgpls, double wfokjodxgnuc) {
double vcgqew = 6444;
string hgkyfaisxpelola = "quwfscechaypuadlgpetgaeuueouocfvaucwpbenosvqzewzgqpmzzfxwtzeuhhjpcyeyjensgm";
bool ykaborr = true;
int xgvkiop = 3519;
bool xzvmozxzxqebcb = true;
return 82128;
}

double giuosve::aiqygmlnqrgwrjti(bool ftxrnpyuh, double usgydoog, bool pjxustqheccbpw, int zyvlnukwvxxwdcm, string kaowgkny, double dvaed, double xescusqrp) {
bool dijxiuhoqpm = true;
double wfjeryykdzal = 8970;
string maxyqiloavwbw = "ibzlzdeeeyekevbqdxnpxdllcincrrphmassgsdezoojpxcuobfrflfgmxxmgkgtcklkhoxynaz";
string sanoxr = "ejczpirhituduwrutkskvmpizrzxjpngkbkadexbhmkrytqacufpeamybxfkpnmsqetioimegbafnzsxwflokkclnkpw";
bool ittlvlslxosc = false;
if (true != true) {
int yrhvh;
for (yrhvh=63; yrhvh > 0; yrhvh--) {
continue;
} 
}
if (string("ibzlzdeeeyekevbqdxnpxdllcincrrphmassgsdezoojpxcuobfrflfgmxxmgkgtcklkhoxynaz") != string("ibzlzdeeeyekevbqdxnpxdllcincrrphmassgsdezoojpxcuobfrflfgmxxmgkgtcklkhoxynaz")) {
int fzddadr;
for (fzddadr=46; fzddadr > 0; fzddadr--) {
continue;
} 
}
if (string("ejczpirhituduwrutkskvmpizrzxjpngkbkadexbhmkrytqacufpeamybxfkpnmsqetioimegbafnzsxwflokkclnkpw") == string("ejczpirhituduwrutkskvmpizrzxjpngkbkadexbhmkrytqacufpeamybxfkpnmsqetioimegbafnzsxwflokkclnkpw")) {
int nap;
for (nap=5; nap > 0; nap--) {
continue;
} 
}
return 39098;
}

void giuosve::nfnkkvpnjyjmkgjnanqyl() {
bool kayheorj = true;
if (true == true) {
int quleu;
for (quleu=17; quleu > 0; quleu--) {
continue;
} 
}
if (true == true) {
int rz;
for (rz=5; rz > 0; rz--) {
continue;
} 
}

}

string giuosve::lbsvuhmjuvlkcwhulujurwc(double zjkoiygk, double pfxpmcbpoq, string zfjhhril, double eerdxs, bool jgdsjawsivbxqwf) {
string lcduguyh = "geavnmddheemwwnjcnyyckfojobzcevdovkvfi";
double rwvwacay = 9615;
double jxlzhrtrwa = 14803;
int sblwpbdv = 629;
string cftjsrbr = "ssieiswkoctpabhzhoqcvmoxwboocmafdbpgfbtdorymvredtikuxylarpalovjpmq";
if (string("ssieiswkoctpabhzhoqcvmoxwboocmafdbpgfbtdorymvredtikuxylarpalovjpmq") == string("ssieiswkoctpabhzhoqcvmoxwboocmafdbpgfbtdorymvredtikuxylarpalovjpmq")) {
int qzagw;
for (qzagw=58; qzagw > 0; qzagw--) {
continue;
} 
}
if (9615 == 9615) {
int rrokmfb;
for (rrokmfb=58; rrokmfb > 0; rrokmfb--) {
continue;
} 
}
return string("myuwtcr");
}

string giuosve::mcmbtjwobrfdmtyhejr(bool ravhyrdrgdj, int pdirxwafy, bool bwqdylggwvp, int mgryckfjeio, bool ayfkre, int onmzhcdrgvr, bool sneictvzodkc) {
double vdparklyboyp = 63460;
int nvihhbuzppwiz = 6191;
bool tlerbnomso = false;
bool nzcotmgldjbb = false;
double gctrtfnc = 33287;
return string("lzdisa");
}

string giuosve::wmtedvxxzdmetwukbs(string ufowkcdblw, int nuszqvuthhv, int mkbrlqburpux, double eaouh, bool efgaamzk, double smobvtmaac, double bygbsyayws, bool bhhhheveujzw, int bllpzdf, int wlslkhxushb) {
return string("o");
}

double giuosve::ronpkyrawjnelvmbnvg() {
double lqdbln = 58576;
bool gopxuyu = false;
string ywfsz = "dxypxuvchddrndztazusmlzw";
int gacxejynps = 7235;
string nyacm = "nntkm";
string fzultccsojbdk = "cmiybowurcomcpshlzbajmjhgcdyiqtkbqhlxciykxnxkzrwqagrwodjdqwgiffaqinmxunkexi";
bool styry = false;
double iudpmlcpbo = 6202;
int qwduuklvj = 453;
int mxgiswygc = 2307;
if (string("nntkm") == string("nntkm")) {
int dfpprvehp;
for (dfpprvehp=87; dfpprvehp > 0; dfpprvehp--) {
continue;
} 
}
if (false == false) {
int egpr;
for (egpr=4; egpr > 0; egpr--) {
continue;
} 
}
if (string("cmiybowurcomcpshlzbajmjhgcdyiqtkbqhlxciykxnxkzrwqagrwodjdqwgiffaqinmxunkexi") == string("cmiybowurcomcpshlzbajmjhgcdyiqtkbqhlxciykxnxkzrwqagrwodjdqwgiffaqinmxunkexi")) {
int vqdpo;
for (vqdpo=66; vqdpo > 0; vqdpo--) {
continue;
} 
}
if (453 != 453) {
int wsr;
for (wsr=38; wsr > 0; wsr--) {
continue;
} 
}
return 31527;
}

string giuosve::xahrhlnmjwwixqabcmuax(string sajwlangpfpm, bool ssvywatcqiendof, bool zhvzmfjvwlqhm, int sxytjx, string tymlfvmxpmra, bool wkwdoqtabku) {
bool avclfhm = false;
string mwnfmfejsp = "qqfqlyhpdqojgkcosysaajkydopsxvzdrvhmyfijtagzjbnmzbnhxqqwvukdaaxaxgguhg";
string qsibdttcicn = "lkqrcumovldhbcaduectaozkirdkzzchsksjkwyrthxihdl";
bool utyaxqpddsvlum = false;
double pzdyncoey = 17041;
string ltbnx = "qvfqwcertbseebyytqcykmrgvsnfpaktuuwmymeiwefrwjgqyzhrujrw";
string eazrireez = "zetcgvoxlmnbkdajlpcxpy";
bool nwzezdwewiw = true;
string ouywnn = "bngpgibqlxpdnrtzjvsrjsoson";
if (string("zetcgvoxlmnbkdajlpcxpy") == string("zetcgvoxlmnbkdajlpcxpy")) {
int bgh;
for (bgh=91; bgh > 0; bgh--) {
continue;
} 
}
if (false == false) {
int wlgjrc;
for (wlgjrc=83; wlgjrc > 0; wlgjrc--) {
continue;
} 
}
return string("cmadollb");
}

int giuosve::jimvsapgrmxvunuzuysu(int jxxgxeyylkxygk, bool afxvospzfcwnrp, double ushfgxyrw, int xorfdibg, string dkeoxquxc) {
string jxzddo = "rummwmbqhaxjwtveuanrsnkxdgksxqqucaixmpijsecoliqbuqyibfhlfprwkktguqezhmmyyrfpzaidnkkuqxigdmhvtbhhdrd";
int gnrshjumtdhaauv = 2591;
double ksgweiktst = 41305;
double iwplutgtnbvvc = 6527;
int ttofybzhflbbasr = 1009;
string rsljrfwchvn = "vjmrkqjefpzjhcqryfohglkdfvadahhotzphaowauwcyhgxsbpoewnopxpsxadqbqkdsyipolxxjbjtwvob";
int llscpldig = 1566;
string vfgfypdax = "dwxhbjmlkxxzlewectoent";
int kaxmhtdkdtqch = 1392;
if (1566 != 1566) {
int gj;
for (gj=60; gj > 0; gj--) {
continue;
} 
}
return 7646;
}

bool giuosve::dpjmnidkee(int vjkqgurmqg, bool boyhbbrmaxm, double pykpvatvdqf) {
double nrpkcgiydvfldao = 1207;
int ecbasugtnocwv = 4280;
string bastcsohiptc = "exdonoctjpzuyplpyqpbwbeienvxaapiexitszwrpaewvtcxsbi";
if (1207 == 1207) {
int gjmv;
for (gjmv=47; gjmv > 0; gjmv--) {
continue;
} 
}
if (1207 != 1207) {
int jnmmy;
for (jnmmy=6; jnmmy > 0; jnmmy--) {
continue;
} 
}
return true;
}

string giuosve::fmidksvwdoyrgd(string colqaxlnfsjawu, string ohtoaevk, string zhqotb, int odlfidehl, double azidwepzxzdgeda, double ultdq, int mbyfgg, bool tjcqbyxrbf, int nmombssbiej) {
string mhuudxb = "bswyhrjlalpjdrhayha";
int eqvdrdqrioqcrhq = 8862;
double nrwzr = 29996;
string uzaspfjpvsi = "sehvdig";
int jvvmhxp = 3651;
int niksttz = 445;
if (29996 != 29996) {
int sdfzawagzr;
for (sdfzawagzr=71; sdfzawagzr > 0; sdfzawagzr--) {
continue;
} 
}
if (3651 != 3651) {
int wppvnhiksj;
for (wppvnhiksj=6; wppvnhiksj > 0; wppvnhiksj--) {
continue;
} 
}
if (445 != 445) {
int lfkbxd;
for (lfkbxd=51; lfkbxd > 0; lfkbxd--) {
continue;
} 
}
return string("ipaas");
}

string giuosve::uqfkbcqucdoujaqzpvgsjhkhk() {
int npkzhcwy = 3157;
bool imiekrgnygjirlk = true;
double qidxgmgosyfxdok = 67267;
string ikeontocw = "ujhyafupytzwntbkrlojtpuqajtgfquxgwwhqxxduwcjpdwfmfklomgactpkmyrzqjzvgpuukwnziyfohloidngbfgdi";
double koqwn = 43703;
bool refhsfmnuyhlrf = false;
bool nurybd = true;
return string("aeoljtdpgusbmqutc");
}

giuosve::giuosve() {
this->nfnkkvpnjyjmkgjnanqyl();
this->lbsvuhmjuvlkcwhulujurwc(10452, 4875, string("vyjreibynndhynpwkerythzknzgryjlaewkwtabbdemkugqihvglgyxkgzipdwnjdfucwkfkvadt"), 25027, false);
this->mcmbtjwobrfdmtyhejr(true, 8257, false, 1174, false, 2379, false);
this->wmtedvxxzdmetwukbs(string("cvvczyfzdciuygzqgreaihprhlgdqtxxsxwvieucwebflpwxrgtifwmzenqsrijuupoxpyhkvxorxaezg"), 1249, 6401, 19084, false, 14873, 35087, false, 2607, 5416);
this->ronpkyrawjnelvmbnvg();
this->xahrhlnmjwwixqabcmuax(string("fuzicvxa"), false, true, 408, string("bvrd"), true);
this->jimvsapgrmxvunuzuysu(2711, false, 17578, 116, string("ybpssmrfabfdpxme"));
this->dpjmnidkee(1326, true, 977);
this->fmidksvwdoyrgd(string("lqdqebetsdtvfjneruxoseamdnyzsz"), string("osxldkqccapkmzpqphvbekfidmwoot"), string("punfnwpkjdkukoluppbibibmjerfwzufwhztiwimjnqliqjatlpom"), 2596, 32438, 13645, 1508, false, 6163);
this->uqfkbcqucdoujaqzpvgsjhkhk();
this->cvgoopjxzvwrtyvmcfnnzyi(813, 2151, string("bldpicghioyvfddebjtfemhmubfxleawfpwpcxgjnrhklgxbajotcgcmimzovytninvnrvmng"), string("t"), true);
this->stcvjrdvfebruxhfmixxcsazh(4493, 26390, 59610, 4617, string("rhqteqznugwaayyzguvnnohbzsekjfyciaebzhaapsjwlzxozuogplfjudphrdvitgxxwrzc"));
this->tqpgtyhcvfakxucbdkd(true, 677);
this->azbgkropkedbpqhx(10817, 1753, 14817, 34291, 3355);
this->aiqygmlnqrgwrjti(false, 11939, true, 260, string("pxxlhhgwwzbjycltrwngdhhhconjltntmnhgsrgkhhelqgqdrddnmcmqvndbjtod"), 4452, 32622);
this->hrgoyoexnlmxrlnazcj(931, string("gciaqudzcwzankjjqvjfwgplccbgcymdbqrkzqzaeswylhpylxhxmvcnygbqjwdljrwowv"), string("qtzugtohtti"), 51137, string("nzvnaswsckdqjrskgtarduexocvkgnxsednzrhhbgzpuircafbqyttllrhizkapjljamdwutsghpdvfm"));
this->joyybdvwnmdcuwf(string("wnblwr"), 3411, false, 3120, string("yjeakiezpbfpkbbbhxxbelvwjvqqxbhxntequvvqvrygxoohlzhvaabhtdfuypqfsqxqieehzgoomkpfqtkcoybxbegmqkcgn"), string("nqn"), 38342, string("kzgytvrqfsgvepbmxsgsihgdqdybqkjsywthgjvjoedxhcrxljszmwsfarpvjirwkcqxpiewtwdswhastuiu"), string("yipyeiqprgyqxxolvekxfbuagpabfxrkkquuevrzscvlxvjtnufhivth"), false);
this->fmsrewrcvq(string("utjpxcctzpeqzqtbxbxmciepsrqmybjtifqasionlezgowqwxsjxpgokgfxrfdzfcqoptfvgwokonjvdodzaltad"));
this->fkpauzmdayovzyiyvcmgyzl(5558, false, 20438, 2160, 442, 15306);
this->esvbweaclf(string("cpkjynvtfvgbqzoyzhdtyzdoicrkdwuxidjfuriubemlfjwzjkqrkezyjubcfzacvnjkmjgoxy"), 8485, false, true, 1459);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class uohbacf {
public:
double gjyixrjaat;
bool qtkrmcdqwgwonm;
uohbacf();
double fhdkvosyilfkrzqsssjg(int ejfmnodqtax, bool gthrcmyaccby, double uletlnj, string lxawamjcdycah, bool tmyeblo);
void suarcusilmfpzedvtbc(double ezyhpzhth, bool faupbwoqfumemb, int sqqnxctppep);

protected:
double ezatvk;
string xeygwqsnesk;
int cywfzyvtjkkrqv;
string zjbeiwvcsftufiz;
string ikvtbqhsemooiv;

double xojcyvqetgqhrehhcursos(string yvplwsdyyznwnjj, double fuvhxep, double cxwls, bool qhaeqnyofh);
string qabwszrwbetkjhvlwhaqqbu(int tjajlnmqrj, double rozsohmnedxci, bool sqzzi, double zjzrmhicbwebe, string jhdvczvr, int rxcnuiopads, int krevcnpapjszng, double lmybfeofpbkja, string bhsbxzxsgvv);
double qnqoxxjmvfl(bool gypcxvyqymwfqjf, double vkwofamyoxxq, double misqivvsuqzh, bool ytzom, double yjajgj, bool qydnxvdnzyq, bool lnpkrcpbzgwzlz, string ihgsfsvx, bool znwrp);
int rexkbqsuimrvd(bool calsgnnuttweyo, int ephlleolym, bool plaqydjojq, int dnhgh, double xjfzisidydf);
void hvgkaqscymnqkmarnn(string chkuo);
string irdnlkivmh(bool qqjgker, string finrsirniehqjoh, int fxlytzv, int ehplqt, bool subanxfwsg, string paaxskvavnox, double onfwxaz, bool cabchlvvnwkjv);
double quuipoypjjhjtjabnmnbu(int ijyifiaocyxr, string bkyjvlcevwfhawl);
int yhxknsistgcctxunoremqcv();
void twauzqegtwxnsreqadrndsmm(string maqwne, string oijeiekdrpzeuxp, string sdufqbmpxvigcoc, bool gykplnltmhyvnsk, string krpuhzlo, double uscptwjc, int aysftzclcfstgo);
double gxnbvxfmzbezg();

private:
double exhdbd;
bool xdggqg;

int mosfkwrydnvxppjbnqtazgvw(double fpxauanhlapjh, bool zkiurpkel, int ehkihdcp, string tffdezqrmswd, double tmrvwmvtfdqpx, int ksafjuany, int rrpmrlvcct);
double bwnixcfrhfzcpbecx(double bgnayemjzcszcut, double rxnuxuaom, double ydzlspxlpz, double ywobdzuk);
void vayrzkjwvcyuoehoa(double kwvxgsn, int godsmotlfmwky, bool dnmlvxht, string sqcbmxhx, double wygebonn, double kgtntivtpouhj, double aswitv, string mgbfn, bool bdbmykikaaoqz, bool qsnjouhwugysosu);
string rgwkprnsvc(string zmkmjrswr, string llirogphjsz, string qyesrzorfhqzf);
int fsyulkvqkzgajgihxt(string jtytyeqagxvg, string otmrjnkxh);
bool ntvndeaauplvimixqiwdcvmp();
int qkvtodellvpztxsemepx(double skipreaxura, double swcpdlwucudtbh);
int jfrelvwcanjkppmicllieh(bool dlcdfwfab, bool ixvfm, int ltrdfxswg, int qptmeetfann, string ycqjpwrp, double emttxhwuml, double efpsz, double tsfws);
string zbxedgiskcvtealjuihdgeewx(bool xdzgnccsjo, bool xosavbezjbkjl, int whqqqsruaqvzjpo, int yutkyt, string vuekumbcrsvj, string bmrfs);

};




int uohbacf::mosfkwrydnvxppjbnqtazgvw(double fpxauanhlapjh, bool zkiurpkel, int ehkihdcp, string tffdezqrmswd, double tmrvwmvtfdqpx, int ksafjuany, int rrpmrlvcct) {
bool gyqryiztlihti = true;
bool jtjqjlylji = false;
string wlddxcc = "czptihzmgktcjxhjogebbawvjcsojqyifysajrxkeuskaowqhkaggjsnuxrwdgtrjns";
int bbptvonheeiiedh = 5599;
bool bixfe = true;
bool auveiikrnlququk = true;
double hyyndd = 28065;
int ijwymm = 6282;
bool eerbldkailzoa = false;
if (false != false) {
int kvcku;
for (kvcku=24; kvcku > 0; kvcku--) {
continue;
} 
}
if (true == true) {
int nexpunz;
for (nexpunz=64; nexpunz > 0; nexpunz--) {
continue;
} 
}
return 75956;
}

double uohbacf::bwnixcfrhfzcpbecx(double bgnayemjzcszcut, double rxnuxuaom, double ydzlspxlpz, double ywobdzuk) {
int huaojap = 1577;
int wnuxl = 2143;
int ccviavhlxdwa = 392;
if (392 == 392) {
int vyacku;
for (vyacku=56; vyacku > 0; vyacku--) {
continue;
} 
}
if (392 == 392) {
int nakoy;
for (nakoy=48; nakoy > 0; nakoy--) {
continue;
} 
}
if (1577 != 1577) {
int oiicwddff;
for (oiicwddff=54; oiicwddff > 0; oiicwddff--) {
continue;
} 
}
if (1577 != 1577) {
int ycfe;
for (ycfe=13; ycfe > 0; ycfe--) {
continue;
} 
}
return 5579;
}

void uohbacf::vayrzkjwvcyuoehoa(double kwvxgsn, int godsmotlfmwky, bool dnmlvxht, string sqcbmxhx, double wygebonn, double kgtntivtpouhj, double aswitv, string mgbfn, bool bdbmykikaaoqz, bool qsnjouhwugysosu) {
bool vdhiafdii = true;
bool ykawzbpcntlt = false;
double rzfrbnqc = 1914;
string wivod = "jzerbblfkbnqemuirebqwoxovilvnrobkitoykgosi";
if (string("jzerbblfkbnqemuirebqwoxovilvnrobkitoykgosi") == string("jzerbblfkbnqemuirebqwoxovilvnrobkitoykgosi")) {
int fknx;
for (fknx=31; fknx > 0; fknx--) {
continue;
} 
}
if (1914 != 1914) {
int gvhen;
for (gvhen=77; gvhen > 0; gvhen--) {
continue;
} 
}
if (false != false) {
int lvewith;
for (lvewith=46; lvewith > 0; lvewith--) {
continue;
} 
}

}

string uohbacf::rgwkprnsvc(string zmkmjrswr, string llirogphjsz, string qyesrzorfhqzf) {
bool kvfkitjzbq = false;
double vnbutezdjmmtlsy = 16135;
int elvyas = 4463;
double yyiwzupppbmho = 34250;
int eddciqgznewob = 1153;
double cqxwvqmsndxhf = 14941;
if (14941 == 14941) {
int arqupxqrv;
for (arqupxqrv=37; arqupxqrv > 0; arqupxqrv--) {
continue;
} 
}
if (1153 == 1153) {
int vfsxduwzlt;
for (vfsxduwzlt=36; vfsxduwzlt > 0; vfsxduwzlt--) {
continue;
} 
}
if (16135 != 16135) {
int zsgasep;
for (zsgasep=32; zsgasep > 0; zsgasep--) {
continue;
} 
}
if (16135 != 16135) {
int pk;
for (pk=94; pk > 0; pk--) {
continue;
} 
}
if (16135 == 16135) {
int byt;
for (byt=4; byt > 0; byt--) {
continue;
} 
}
return string("cudbm");
}

int uohbacf::fsyulkvqkzgajgihxt(string jtytyeqagxvg, string otmrjnkxh) {
double hzricpeivmy = 53295;
if (53295 == 53295) {
int gbcvxts;
for (gbcvxts=19; gbcvxts > 0; gbcvxts--) {
continue;
} 
}
if (53295 != 53295) {
int gkjemk;
for (gkjemk=52; gkjemk > 0; gkjemk--) {
continue;
} 
}
return 15954;
}

bool uohbacf::ntvndeaauplvimixqiwdcvmp() {
string jtnldjceoj = "brwctjpnbhgssnlhosyuqufyksbcevzfallfehdulwzthyq";
bool ssupdnm = false;
int etameik = 8558;
double ecfoxuvmsir = 58249;
if (false == false) {
int mmtjshfycc;
for (mmtjshfycc=15; mmtjshfycc > 0; mmtjshfycc--) {
continue;
} 
}
if (string("brwctjpnbhgssnlhosyuqufyksbcevzfallfehdulwzthyq") == string("brwctjpnbhgssnlhosyuqufyksbcevzfallfehdulwzthyq")) {
int groxlbd;
for (groxlbd=7; groxlbd > 0; groxlbd--) {
continue;
} 
}
return true;
}

int uohbacf::qkvtodellvpztxsemepx(double skipreaxura, double swcpdlwucudtbh) {
bool wggeobqi = true;
double hwqrofin = 7763;
int tixssktlcb = 719;
bool wwfljimznor = true;
bool iswgjamyzamx = true;
double sysgjreiptgddid = 18160;
double pvuvgttwiacul = 9031;
double ahmsebi = 20536;
if (true == true) {
int ops;
for (ops=98; ops > 0; ops--) {
continue;
} 
}
if (true != true) {
int wih;
for (wih=68; wih > 0; wih--) {
continue;
} 
}
if (9031 != 9031) {
int hegdobmjh;
for (hegdobmjh=76; hegdobmjh > 0; hegdobmjh--) {
continue;
} 
}
if (true == true) {
int fcuqy;
for (fcuqy=64; fcuqy > 0; fcuqy--) {
continue;
} 
}
return 96522;
}

int uohbacf::jfrelvwcanjkppmicllieh(bool dlcdfwfab, bool ixvfm, int ltrdfxswg, int qptmeetfann, string ycqjpwrp, double emttxhwuml, double efpsz, double tsfws) {
string qqdwbarygk = "yjsdghfomqofejudlqpaxblbursxmcatwxpzvguzdmyjvvsoipqxjrfhmlqncdldlqvxfdiqrstvjfrkupjqhbxqpnghchm";
bool imcfjmea = true;
double vusfc = 36541;
int rtmikpsyrdn = 12;
bool ymaqidjeht = false;
bool ddqpao = false;
string xrudrtu = "lxonezpotujgwwixahktxpztiicxdcymhwytpvdklhnunjal";
string isihtzmlh = "eogmuzierhwpzzunjasmsmkgtwidigjnr";
int hshpsyh = 5615;
bool xslhfrttxefom = false;
return 26079;
}

string uohbacf::zbxedgiskcvtealjuihdgeewx(bool xdzgnccsjo, bool xosavbezjbkjl, int whqqqsruaqvzjpo, int yutkyt, string vuekumbcrsvj, string bmrfs) {
bool acijlskjycjnl = true;
bool drjxil = true;
string woiogurtdocb = "hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx";
if (string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx") == string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx")) {
int pwuy;
for (pwuy=47; pwuy > 0; pwuy--) {
continue;
} 
}
if (string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx") != string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx")) {
int bqur;
for (bqur=53; bqur > 0; bqur--) {
continue;
} 
}
if (string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx") == string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx")) {
int nuidqarelw;
for (nuidqarelw=46; nuidqarelw > 0; nuidqarelw--) {
continue;
} 
}
if (string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx") == string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx")) {
int wpvmihxvh;
for (wpvmihxvh=96; wpvmihxvh > 0; wpvmihxvh--) {
continue;
} 
}
if (string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx") != string("hdxobwceqfrrpnaiwtxrhhufjufeccvkqattfzvmegmhkvtjfqxijueqx")) {
int goukemi;
for (goukemi=96; goukemi > 0; goukemi--) {
continue;
} 
}
return string("");
}

double uohbacf::xojcyvqetgqhrehhcursos(string yvplwsdyyznwnjj, double fuvhxep, double cxwls, bool qhaeqnyofh) {
double rrlhhvyz = 6690;
double umdqmm = 17613;
string ukqwdy = "mcwgenfchgdlluoqfvzaadrytrirupfnnmlpfj";
int mgfopuniuvils = 1129;
int ldkwmqycvjry = 1323;
int ptueycpc = 3364;
bool kbitb = false;
if (17613 != 17613) {
int he;
for (he=27; he > 0; he--) {
continue;
} 
}
return 62875;
}

string uohbacf::qabwszrwbetkjhvlwhaqqbu(int tjajlnmqrj, double rozsohmnedxci, bool sqzzi, double zjzrmhicbwebe, string jhdvczvr, int rxcnuiopads, int krevcnpapjszng, double lmybfeofpbkja, string bhsbxzxsgvv) {
int swvozlgnttpeek = 4703;
int sbljzq = 3683;
int qhmfionhfeow = 1476;
bool disrlfszunzbd = true;
if (1476 == 1476) {
int gzzjtch;
for (gzzjtch=10; gzzjtch > 0; gzzjtch--) {
continue;
} 
}
return string("vlyeapixygdnuacsy");
}

double uohbacf::qnqoxxjmvfl(bool gypcxvyqymwfqjf, double vkwofamyoxxq, double misqivvsuqzh, bool ytzom, double yjajgj, bool qydnxvdnzyq, bool lnpkrcpbzgwzlz, string ihgsfsvx, bool znwrp) {
double ndtfxt = 2524;
int jljeuw = 500;
double jkalinu = 40081;
string egdoqkgvw = "gycewhcvwduwkgvpvtchuaomnczawcmbfkisqvuqviddavktmbguwenekwhzpmfeyzyzucjdagygefkxwgjpmkczulnoujdj";
int wdfbnmwf = 8133;
if (2524 != 2524) {
int xu;
for (xu=47; xu > 0; xu--) {
continue;
} 
}
return 33624;
}

int uohbacf::rexkbqsuimrvd(bool calsgnnuttweyo, int ephlleolym, bool plaqydjojq, int dnhgh, double xjfzisidydf) {
return 19158;
}

void uohbacf::hvgkaqscymnqkmarnn(string chkuo) {
int xtfajri = 1067;
string gkbswv = "hpmfkbvbhkixqynxupyfdlicojsxkoutotefcrql";
double wriqh = 24834;
int ualepwynzkw = 8220;
int qukucmwrbbwtlt = 3830;
string tlsjbhjsbug = "ylncaeheqwdqo";
string fwtkyhurcruzl = "mfcbghhrfwfevyly";
int gbbytfp = 1211;
int uvwfy = 5737;
if (3830 != 3830) {
int lsouof;
for (lsouof=28; lsouof > 0; lsouof--) {
continue;
} 
}
if (string("mfcbghhrfwfevyly") == string("mfcbghhrfwfevyly")) {
int os;
for (os=62; os > 0; os--) {
continue;
} 
}
if (5737 != 5737) {
int trekeriv;
for (trekeriv=11; trekeriv > 0; trekeriv--) {
continue;
} 
}

}

string uohbacf::irdnlkivmh(bool qqjgker, string finrsirniehqjoh, int fxlytzv, int ehplqt, bool subanxfwsg, string paaxskvavnox, double onfwxaz, bool cabchlvvnwkjv) {
double nrgmbhcjtuna = 35982;
int yjwlsmzzwrprqrk = 28;
bool tssypsb = true;
bool bfduobikduanfp = false;
return string("xmrnysaepq");
}

double uohbacf::quuipoypjjhjtjabnmnbu(int ijyifiaocyxr, string bkyjvlcevwfhawl) {
int wogqcwwhnqvrx = 7480;
bool wrjkheslmxacswa = true;
int qijjkzkrkkg = 6384;
string ixagusyd = "cqetttdvtejxwjchnmvfgucczmzfpoxpsezhhkfhaqqopahvrcqif";
bool rlpmsnwzy = false;
if (6384 != 6384) {
int tdgceq;
for (tdgceq=93; tdgceq > 0; tdgceq--) {
continue;
} 
}
if (string("cqetttdvtejxwjchnmvfgucczmzfpoxpsezhhkfhaqqopahvrcqif") == string("cqetttdvtejxwjchnmvfgucczmzfpoxpsezhhkfhaqqopahvrcqif")) {
int ezmfvbf;
for (ezmfvbf=68; ezmfvbf > 0; ezmfvbf--) {
continue;
} 
}
if (false != false) {
int cp;
for (cp=52; cp > 0; cp--) {
continue;
} 
}
if (7480 == 7480) {
int mpfkdeal;
for (mpfkdeal=4; mpfkdeal > 0; mpfkdeal--) {
continue;
} 
}
return 1368;
}

int uohbacf::yhxknsistgcctxunoremqcv() {
bool dswigzsj = true;
string dvqnpmsnqncsv = "fvomknieswfkgbdeawzlhaqwmhrxtnsxdvdgzejnapmeilcrmlkaojtuvioaicsybgifgmjnfmftmscjoggniosqoxrbua";
double xhjbl = 3324;
double xdzxtvwiarlffhb = 928;
string luuwjbwqreqwbbs = "dovtjixiiifwgnddqqujhnaopzrgbekwpytlgcdjjzrhhkbzuyuzotuamvqutbhxmzyk";
string gwysgqhyce = "fiknxqvploenezhushnkyhlwnqmabxvejbhmmgbdariuaxrpvynghvunnzbrlhwwvtvksqsaiewewlhslcezujindpxw";
string mfjxkf = "bimfdvbinpuhaf";
bool geeuftmufkvtg = true;
bool tuzgsqarv = false;
if (false == false) {
int xkirj;
for (xkirj=16; xkirj > 0; xkirj--) {
continue;
} 
}
if (string("bimfdvbinpuhaf") != string("bimfdvbinpuhaf")) {
int oy;
for (oy=28; oy > 0; oy--) {
continue;
} 
}
return 76337;
}

void uohbacf::twauzqegtwxnsreqadrndsmm(string maqwne, string oijeiekdrpzeuxp, string sdufqbmpxvigcoc, bool gykplnltmhyvnsk, string krpuhzlo, double uscptwjc, int aysftzclcfstgo) {

}

double uohbacf::gxnbvxfmzbezg() {
double upinjyrcsdkzsn = 10479;
bool ieajjzeoeyj = false;
string ujntnoferlmnf = "gvdubwgiwurhkirdikatyjofqoejjwmuvpfxvzpnfghqxkfjqmaylgmwvgamhsfiqrfkigkhj";
double qqsbsrvpqoqtqb = 70706;
bool nsbmyhtxjy = true;
int iahmng = 2591;
double xmfsvlwyej = 15473;
bool gbxrgkni = true;
bool drzzdcvninmshd = false;
int nkfixqxklzlv = 3534;
if (3534 == 3534) {
int kxgirssn;
for (kxgirssn=82; kxgirssn > 0; kxgirssn--) {
continue;
} 
}
if (false != false) {
int bkkiykfogg;
for (bkkiykfogg=38; bkkiykfogg > 0; bkkiykfogg--) {
continue;
} 
}
if (false != false) {
int eluwrvcx;
for (eluwrvcx=53; eluwrvcx > 0; eluwrvcx--) {
continue;
} 
}
if (70706 == 70706) {
int aoarzovdez;
for (aoarzovdez=14; aoarzovdez > 0; aoarzovdez--) {
continue;
} 
}
if (true != true) {
int eegu;
for (eegu=46; eegu > 0; eegu--) {
continue;
} 
}
return 11647;
}

double uohbacf::fhdkvosyilfkrzqsssjg(int ejfmnodqtax, bool gthrcmyaccby, double uletlnj, string lxawamjcdycah, bool tmyeblo) {
int rmfawzwejn = 616;
double xhmjseom = 25500;
double mgfcxt = 64884;
string opnwmkupuzzf = "pnzexmnexttfdxhzbvilzbpeznkee";
if (25500 != 25500) {
int ykxpzww;
for (ykxpzww=43; ykxpzww > 0; ykxpzww--) {
continue;
} 
}
return 54042;
}

void uohbacf::suarcusilmfpzedvtbc(double ezyhpzhth, bool faupbwoqfumemb, int sqqnxctppep) {
double tgjyifrzh = 10049;
bool blhhcbh = false;
string mykgepj = "nzihtvcglhye";
string hueuhq = "qxlqjmkvjqrjbwobrycxbrcgigqnkzmpxgwtuzswwxoryeejypgiamadpnkxtznoyssnaeniemuxzib";
int qzxhfoyzatu = 1725;
int ekuedqvlpmzo = 3280;
double jdqvlpkq = 11714;
double twcimsywsy = 1092;
bool mujolwqh = true;
int bynzhxpjaf = 2103;
if (1725 != 1725) {
int avglq;
for (avglq=73; avglq > 0; avglq--) {
continue;
} 
}

}

uohbacf::uohbacf() {
this->fhdkvosyilfkrzqsssjg(991, false, 18127, string("ctbzvmrvlozqcvwjhjhenpmdzleyskyzruutznzhzuzmqwrjdqhwwseusmjwyie"), true);
this->suarcusilmfpzedvtbc(59028, true, 2272);
this->xojcyvqetgqhrehhcursos(string("bawurccuzsfycbaesznxamibmufsglotgpqwapwlluivsxfgxhnxgqfrerukowvydtabv"), 43271, 716, false);
this->qabwszrwbetkjhvlwhaqqbu(5244, 27216, true, 19425, string("ijuvjiouhlnlaoom"), 628, 2535, 9407, string("pscfvlclmmahcdfpthvlruevlbuncwuiqhlfkkuqjcjcfgcqghfgwnctdkavnwjtmpprrzrfrobnrnajlvpe"));
this->qnqoxxjmvfl(true, 38221, 9870, false, 20163, true, true, string("hdegfdjnxigdqsmyvitbcezckgzuogkzwntkbbpzvd"), false);
this->rexkbqsuimrvd(false, 2432, true, 228, 22533);
this->hvgkaqscymnqkmarnn(string("cekuqrvpowfkeysagqlhpacgwxavqoxeqj"));
this->irdnlkivmh(true, string("gyfnnwkznufecepqlceoptbaxyuikoflaatbdkfunluaupstjgjdxmkrykpotorhrzqivylzpivpiaxugwkkbofwvaguzenelk"), 330, 7095, true, string("wkkkxxjsqsygocjtfssuwmhyhptvarzsjxuejpbodvuswjandvfiwpujqc"), 6978, false);
this->quuipoypjjhjtjabnmnbu(2275, string("wbbtmptoehnhpetutnrbxyhdndfasgruqatdqakgbszwcrzzwpoamnnpfuulnzprlpymjmkgqcknciwdyw"));
this->yhxknsistgcctxunoremqcv();
this->twauzqegtwxnsreqadrndsmm(string("seyocxgxsanraaawpopqhcswqxzcdlybfqrchhaakxewblnaakxqxfcivpub"), string("yuoqkezulcmntkhkopwnjdnarwmepoxjntpgsqrkqtwxifbrgdpl"), string("nsdrqtojnhvvzktcvapnqeirvcakxvkrgmykujmtucqioywpdevgfihvvrmswyluffkrywhgymmdqllvl"), true, string("fkhj"), 18523, 5660);
this->gxnbvxfmzbezg();
this->mosfkwrydnvxppjbnqtazgvw(70793, false, 9472, string("rgmsthqhjzeimfvqqtcsmroqngrrunlatqaeubqtsgzfnocrkbuvwvmbyshfgffbkgiyfqrsluiujxvstkmyile"), 507, 141, 186);
this->bwnixcfrhfzcpbecx(59018, 64121, 5786, 25166);
this->vayrzkjwvcyuoehoa(2158, 681, true, string("vkmzzvzlfreantmaktxdodzmjzmlzxipjccylbvldyqfjh"), 29727, 1664, 4430, string("sbqksfcgaueoqrdvahpyrnbojktnmkmwptzwesatrnircuwmoxhhvbtlepiverpwkywfzt"), false, true);
this->rgwkprnsvc(string("mfvhsrqyxopyxofrjmrvssgxfuilbuetanndg"), string("gghijdffzfiwvzuhkzetzcupckdqzucqfheihtgvjfhxgemsdapfhrslppzuomboyryhcwvslvmgmbdjwxknxlwupfbjx"), string("cxopqoubsrobbviyfatmjxzjedgjtetsuxndqgrlmrkgjhqppnkfcyxgxveduksyunpelapfa"));
this->fsyulkvqkzgajgihxt(string("yudpbveejsoopwnuvoqmyxuzeyqfqtkycvlznuedhswbnq"), string("cmbzcostdgg"));
this->ntvndeaauplvimixqiwdcvmp();
this->qkvtodellvpztxsemepx(9919, 3085);
this->jfrelvwcanjkppmicllieh(true, true, 102, 3355, string("tkgsnzuacvsarprikgihkynoxeweidipckmaxxtvzisxfekrhvznxaaaeayfsczhmb"), 22381, 65091, 38951);
this->zbxedgiskcvtealjuihdgeewx(true, true, 8187, 1593, string("asnrgnakychifakiciehkscbkecfvuimvuvolawouisugbyimrgqjlnktqukfrkidnpaebt"), string("aroppfifuaohzupksgupaysktxqfoyuqchqlytolinspgjydumqwaiitrpfvrngxilcjxosqbvmqfkmuqwziakeiifma"));
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ehwxqcr {
public:
bool pijcrcctliuaibm;
bool wdofab;
string ojeunlrs;
string fzgwkkqyxobqe;
bool jbykpcmfjoesh;
ehwxqcr();
void brjgmeszebm(bool hzjmvaoo, int coxlfndnurinzo, double nzlnlgom);
void bhschlulpvvuwwozmqjawjq(string yanujmzies);
string okbikkjvafeuvbozdsa();
double mbymsbvejq(int mcroqb, bool puhylxxs, string jpsxrfbqlcvnvz, int ndznns);
string xxxsiykvko(int osequfeiwy, int gnwpjbwcqwfyixe, int eicheddd, string rndljrufz, bool xknxihva, bool fsdqwuoqdxz, double fscygdrh, int rswjwfbhz, string rvqbsxogmylmw, int otqtarwyphvlzbl);
double ydrgazrdytpslr(double tuofrgmvreq, bool mussuraq, double jvgcoecq, double dfcmbhqyfzxmzqi, bool htzjb, bool qacuwluoophzn);
bool bayzrwldjxicxobnozubyo(int iveceqk, int strgevpktudj, bool fnjezz, int gadbltozcejpi, string xwlbkndbahlogmy);
string vkduwnmasksalfjkixc(string flvml, double iyubspxbd, bool qtdeyqzuqq, int cwoqrlkzfk, double hvsmaxqvbnvf, bool sjaswuf);

protected:
bool gbxpjcjkx;
int nutoaxdahywsy;

void yiafosyqyovvzfmhwrvzk();
void jfdkxexvigstiisvlkbo(int xugmdvkdzlw, double odshsaw, int iatuurfmbqdryv, double ggcskllrz);
void lubskwwlktdxrwftnbfico(string rbwyngkdeyze, string peirmilmmqkfa);
bool becwbdoodszruauqcjetqcm(string prxomfm, int umphx, bool wtsdvsqmtqjfwfk, double foxytmaqecl, int dkwayvwnesnaj, string fmchxxjrs, bool oxciftstfxy, bool owwuxrsbal, bool kuqxotfy);
double ofiltmzneankz(int mklrmfvcabxmbz, string psgzghuyog);

private:
bool qmfotbglrwhiuzw;
int yibddd;
double wmoktdw;
double hqgngcgcyt;
double hcyitdxet;

int uhbwyduhvggcezmozjqu(int ophzcmnyghtajy, double ecbeupij);
int htrxsxbixzyck(bool dddnoqvfrf, string josrangik, string shgrpullcvnpl, double cyjtei, int pquaecfnzdnr, bool wzuwuediar);
bool libujmlbwk(string wyfikbeyte, bool pnzawphaworodax, bool lchikkx, string lklwnslij);
double lwwphggngrnks(string wcnzkayrbbeaqbj, double frztlcbiqzaowb, double idzegfxbx, double spkmvbwmyqtve, string pzunpogl, bool ejxdisjvfxnj);
bool gatjrtuvgssdrfetaykvkyybl(int wmnlamvarinp, bool fqbqtiblfeyfyq, bool kxvxcmvgmdhr);
bool ofqjilgubl(bool drngbson);
void ztebjyvqtdqx(double lfokfyxhjq);
string tzjgyhqgmarks();

};




int ehwxqcr::uhbwyduhvggcezmozjqu(int ophzcmnyghtajy, double ecbeupij) {
bool erlwozrebgsy = false;
if (false == false) {
int lpvj;
for (lpvj=18; lpvj > 0; lpvj--) {
continue;
} 
}
if (false == false) {
int mrard;
for (mrard=74; mrard > 0; mrard--) {
continue;
} 
}
return 45954;
}

int ehwxqcr::htrxsxbixzyck(bool dddnoqvfrf, string josrangik, string shgrpullcvnpl, double cyjtei, int pquaecfnzdnr, bool wzuwuediar) {
string shxmfsht = "hfjoivnkjizaetevcwuyensjnrxpsqdxmzegpixiu";
int hhmscsgzysvcmym = 189;
bool msdtpna = true;
if (string("hfjoivnkjizaetevcwuyensjnrxpsqdxmzegpixiu") == string("hfjoivnkjizaetevcwuyensjnrxpsqdxmzegpixiu")) {
int wubfmpj;
for (wubfmpj=5; wubfmpj > 0; wubfmpj--) {
continue;
} 
}
if (string("hfjoivnkjizaetevcwuyensjnrxpsqdxmzegpixiu") == string("hfjoivnkjizaetevcwuyensjnrxpsqdxmzegpixiu")) {
int kluy;
for (kluy=34; kluy > 0; kluy--) {
continue;
} 
}
if (string("hfjoivnkjizaetevcwuyensjnrxpsqdxmzegpixiu") != string("hfjoivnkjizaetevcwuyensjnrxpsqdxmzegpixiu")) {
int msfoxkdkgg;
for (msfoxkdkgg=23; msfoxkdkgg > 0; msfoxkdkgg--) {
continue;
} 
}
if (true == true) {
int zf;
for (zf=12; zf > 0; zf--) {
continue;
} 
}
return 91491;
}

bool ehwxqcr::libujmlbwk(string wyfikbeyte, bool pnzawphaworodax, bool lchikkx, string lklwnslij) {
bool uicdscnryxj = true;
int riiktiiyloewys = 1382;
int mhdcfrpm = 611;
if (true == true) {
int jmnbwgxolq;
for (jmnbwgxolq=20; jmnbwgxolq > 0; jmnbwgxolq--) {
continue;
} 
}
if (1382 == 1382) {
int nbauc;
for (nbauc=60; nbauc > 0; nbauc--) {
continue;
} 
}
if (1382 != 1382) {
int xkqnqbwcx;
for (xkqnqbwcx=33; xkqnqbwcx > 0; xkqnqbwcx--) {
continue;
} 
}
if (1382 == 1382) {
int ttccvbrriv;
for (ttccvbrriv=25; ttccvbrriv > 0; ttccvbrriv--) {
continue;
} 
}
if (611 == 611) {
int guslbjcue;
for (guslbjcue=35; guslbjcue > 0; guslbjcue--) {
continue;
} 
}
return false;
}

double ehwxqcr::lwwphggngrnks(string wcnzkayrbbeaqbj, double frztlcbiqzaowb, double idzegfxbx, double spkmvbwmyqtve, string pzunpogl, bool ejxdisjvfxnj) {
string ltgnujplkiqis = "rfmemtnqrjsthzscygiggauzckzpr";
int yxovohb = 8404;
bool xkilpcnauyxbq = true;
if (8404 == 8404) {
int bsfevlbetc;
for (bsfevlbetc=93; bsfevlbetc > 0; bsfevlbetc--) {
continue;
} 
}
if (8404 != 8404) {
int rrmuzryyj;
for (rrmuzryyj=84; rrmuzryyj > 0; rrmuzryyj--) {
continue;
} 
}
return 57180;
}

bool ehwxqcr::gatjrtuvgssdrfetaykvkyybl(int wmnlamvarinp, bool fqbqtiblfeyfyq, bool kxvxcmvgmdhr) {
return false;
}

bool ehwxqcr::ofqjilgubl(bool drngbson) {
return false;
}

void ehwxqcr::ztebjyvqtdqx(double lfokfyxhjq) {
string yotehp = "cybeosqqpvnjlkxcipebxmtiscmzbyxdrwbfucfmhwyohnrysoew";

}

string ehwxqcr::tzjgyhqgmarks() {
bool upyfojohxfq = true;
bool cenmi = true;
string toyzecwnpxne = "cjjgkvfjyprttxufjdthdjggeawwuzsefkwlmjzpojfysanmbn";
if (true != true) {
int zdatjkbf;
for (zdatjkbf=17; zdatjkbf > 0; zdatjkbf--) {
continue;
} 
}
if (true != true) {
int rkhrovdlr;
for (rkhrovdlr=36; rkhrovdlr > 0; rkhrovdlr--) {
continue;
} 
}
return string("xyipufvxeddppn");
}

void ehwxqcr::yiafosyqyovvzfmhwrvzk() {
double eyeyaaptzkfwyuq = 15833;
bool vpfoofxqegu = true;
double kdcrpnhypeyn = 57966;
int wljwvprzvn = 7410;
if (57966 != 57966) {
int yqykc;
for (yqykc=35; yqykc > 0; yqykc--) {
continue;
} 
}

}

void ehwxqcr::jfdkxexvigstiisvlkbo(int xugmdvkdzlw, double odshsaw, int iatuurfmbqdryv, double ggcskllrz) {

}

void ehwxqcr::lubskwwlktdxrwftnbfico(string rbwyngkdeyze, string peirmilmmqkfa) {
int oqxjbzy = 4936;
if (4936 == 4936) {
int uasrhpkr;
for (uasrhpkr=67; uasrhpkr > 0; uasrhpkr--) {
continue;
} 
}
if (4936 != 4936) {
int pon;
for (pon=83; pon > 0; pon--) {
continue;
} 
}
if (4936 == 4936) {
int wnb;
for (wnb=34; wnb > 0; wnb--) {
continue;
} 
}

}

bool ehwxqcr::becwbdoodszruauqcjetqcm(string prxomfm, int umphx, bool wtsdvsqmtqjfwfk, double foxytmaqecl, int dkwayvwnesnaj, string fmchxxjrs, bool oxciftstfxy, bool owwuxrsbal, bool kuqxotfy) {
string qvpbv = "ottirxfxdtqulpjwtlqnmgqvwkkujaywwzgomyzomapzyznsxrtlvbdlqvdiawstfdaclsxwsztvkaecyhmueqgsziq";
return false;
}

double ehwxqcr::ofiltmzneankz(int mklrmfvcabxmbz, string psgzghuyog) {
return 66549;
}

void ehwxqcr::brjgmeszebm(bool hzjmvaoo, int coxlfndnurinzo, double nzlnlgom) {
bool rcdprnakqykxgxp = false;
double vlpis = 24803;
int sjabuxldff = 1965;
bool irgykfyt = false;
bool xytfckqyas = false;
bool prspgy = true;
bool rjfnarqhtszqoem = true;
double nqkzbetbi = 38501;
string snkwkxdzya = "maecoksnfpcwemgvihearemoalfbxkuhozvhmkttphjysqqwtpzgdm";
if (true != true) {
int oygdy;
for (oygdy=55; oygdy > 0; oygdy--) {
continue;
} 
}

}

void ehwxqcr::bhschlulpvvuwwozmqjawjq(string yanujmzies) {
bool bwiswffappqh = true;
bool oiijunquft = false;
bool vonxkwaa = false;
string qozezual = "tsdrowvritedpgqaaylhmshvntkmqnezoedqemqw";
string xcyyl = "ysmueiibzrcmqzpwhfkdnndwwbvucuananqdntltgqvdqrfltiegkcedmxgekphcrcmpjrfblbsufslvzlbqvslq";
if (true == true) {
int afbiocsb;
for (afbiocsb=95; afbiocsb > 0; afbiocsb--) {
continue;
} 
}
if (string("ysmueiibzrcmqzpwhfkdnndwwbvucuananqdntltgqvdqrfltiegkcedmxgekphcrcmpjrfblbsufslvzlbqvslq") != string("ysmueiibzrcmqzpwhfkdnndwwbvucuananqdntltgqvdqrfltiegkcedmxgekphcrcmpjrfblbsufslvzlbqvslq")) {
int ucjtt;
for (ucjtt=95; ucjtt > 0; ucjtt--) {
continue;
} 
}

}

string ehwxqcr::okbikkjvafeuvbozdsa() {
string ltfefmasddaqdlj = "rccjsxfbcpplbdsciyl";
string fhhhkvi = "dbntvmafjq";
double fphfxbuawe = 2946;
string kzzcdbecsb = "amkxzdckwgmrzcplkawmphqzomteiqdg";
if (string("amkxzdckwgmrzcplkawmphqzomteiqdg") != string("amkxzdckwgmrzcplkawmphqzomteiqdg")) {
int joc;
for (joc=63; joc > 0; joc--) {
continue;
} 
}
if (string("rccjsxfbcpplbdsciyl") != string("rccjsxfbcpplbdsciyl")) {
int qmhnatp;
for (qmhnatp=51; qmhnatp > 0; qmhnatp--) {
continue;
} 
}
if (2946 == 2946) {
int bfyozmda;
for (bfyozmda=12; bfyozmda > 0; bfyozmda--) {
continue;
} 
}
if (string("dbntvmafjq") == string("dbntvmafjq")) {
int hvbegtl;
for (hvbegtl=70; hvbegtl > 0; hvbegtl--) {
continue;
} 
}
return string("bq");
}

double ehwxqcr::mbymsbvejq(int mcroqb, bool puhylxxs, string jpsxrfbqlcvnvz, int ndznns) {
bool zeuyvkwkd = false;
bool cleommkxeeqp = false;
bool zlzzrgthfng = false;
double djbqq = 3791;
bool pgdkpgjqdqq = false;
string sdgmvvrlivrwdli = "dzwwkgwyciiqpvnrqzgshawgaqpxmlmdchvzudwrxaxydon";
string flswlqrft = "awtxrpijqlntzgsvp";
if (string("awtxrpijqlntzgsvp") != string("awtxrpijqlntzgsvp")) {
int htp;
for (htp=68; htp > 0; htp--) {
continue;
} 
}
if (false != false) {
int jqlvox;
for (jqlvox=68; jqlvox > 0; jqlvox--) {
continue;
} 
}
if (false == false) {
int fhlrdqvxru;
for (fhlrdqvxru=46; fhlrdqvxru > 0; fhlrdqvxru--) {
continue;
} 
}
if (false == false) {
int mcgydb;
for (mcgydb=9; mcgydb > 0; mcgydb--) {
continue;
} 
}
if (false != false) {
int ry;
for (ry=38; ry > 0; ry--) {
continue;
} 
}
return 13778;
}

string ehwxqcr::xxxsiykvko(int osequfeiwy, int gnwpjbwcqwfyixe, int eicheddd, string rndljrufz, bool xknxihva, bool fsdqwuoqdxz, double fscygdrh, int rswjwfbhz, string rvqbsxogmylmw, int otqtarwyphvlzbl) {
int vojrxcbndohr = 565;
double fmfcyjhlc = 34238;
int nltzkhkasymqx = 175;
string jkszraaqxjj = "ijxlydayeaoqxzjozjllojfqcdlhtdmjfacwniieisbgzrm";
string slfrjjpow = "ihsrsgbpfrqgvsmhsigurwzwsfsfegzlv";
bool strgtrqxnjhhywp = false;
if (34238 != 34238) {
int esofdvm;
for (esofdvm=29; esofdvm > 0; esofdvm--) {
continue;
} 
}
if (565 == 565) {
int wyds;
for (wyds=28; wyds > 0; wyds--) {
continue;
} 
}
if (string("ihsrsgbpfrqgvsmhsigurwzwsfsfegzlv") == string("ihsrsgbpfrqgvsmhsigurwzwsfsfegzlv")) {
int wkmc;
for (wkmc=55; wkmc > 0; wkmc--) {
continue;
} 
}
if (175 != 175) {
int unyyy;
for (unyyy=52; unyyy > 0; unyyy--) {
continue;
} 
}
return string("ktqhdmafxcvvcxqngc");
}

double ehwxqcr::ydrgazrdytpslr(double tuofrgmvreq, bool mussuraq, double jvgcoecq, double dfcmbhqyfzxmzqi, bool htzjb, bool qacuwluoophzn) {
double gxouy = 1211;
if (1211 == 1211) {
int ldpnjrja;
for (ldpnjrja=86; ldpnjrja > 0; ldpnjrja--) {
continue;
} 
}
if (1211 == 1211) {
int dla;
for (dla=57; dla > 0; dla--) {
continue;
} 
}
if (1211 == 1211) {
int rmp;
for (rmp=41; rmp > 0; rmp--) {
continue;
} 
}
if (1211 != 1211) {
int izvi;
for (izvi=69; izvi > 0; izvi--) {
continue;
} 
}
if (1211 != 1211) {
int gvp;
for (gvp=0; gvp > 0; gvp--) {
continue;
} 
}
return 36479;
}

bool ehwxqcr::bayzrwldjxicxobnozubyo(int iveceqk, int strgevpktudj, bool fnjezz, int gadbltozcejpi, string xwlbkndbahlogmy) {
bool ebeyzikspmq = false;
bool vhcdqebj = true;
int kbstpqbuqil = 730;
int pjgqujdkbz = 2247;
int crruoepwxiuthr = 4989;
double bcykftlrjgw = 87858;
if (730 != 730) {
int imqd;
for (imqd=93; imqd > 0; imqd--) {
continue;
} 
}
if (4989 == 4989) {
int ktkuvsqvc;
for (ktkuvsqvc=99; ktkuvsqvc > 0; ktkuvsqvc--) {
continue;
} 
}
if (4989 != 4989) {
int rnbzv;
for (rnbzv=28; rnbzv > 0; rnbzv--) {
continue;
} 
}
if (4989 == 4989) {
int vcmlpxtppl;
for (vcmlpxtppl=14; vcmlpxtppl > 0; vcmlpxtppl--) {
continue;
} 
}
if (87858 != 87858) {
int lvt;
for (lvt=97; lvt > 0; lvt--) {
continue;
} 
}
return false;
}

string ehwxqcr::vkduwnmasksalfjkixc(string flvml, double iyubspxbd, bool qtdeyqzuqq, int cwoqrlkzfk, double hvsmaxqvbnvf, bool sjaswuf) {
int xwoiavvhfiphdon = 2144;
double bzfiwkrfbsw = 24823;
int syebnjb = 6924;
string xybopdyiu = "tjwhwxwfezfcbtzyugslaomxvjowvzcfnyozs";
if (6924 != 6924) {
int usjrqst;
for (usjrqst=73; usjrqst > 0; usjrqst--) {
continue;
} 
}
if (24823 == 24823) {
int njvfzpw;
for (njvfzpw=72; njvfzpw > 0; njvfzpw--) {
continue;
} 
}
return string("ifitlbzvse");
}

ehwxqcr::ehwxqcr() {
this->brjgmeszebm(true, 1482, 5162);
this->bhschlulpvvuwwozmqjawjq(string("iewedwohauivdloonhqkmmvlwklbzrwpxrlkdklemrmiixpancwanppjrxfgcayevnoxjjwrfwgehoqrlctttxkqa"));
this->okbikkjvafeuvbozdsa();
this->mbymsbvejq(974, false, string("efpaq"), 2774);
this->xxxsiykvko(87, 2824, 6790, string("gymsdvsyuwtykqlgnzvyokdrtakercphycpnlzfqvojseiyhegvghvx"), true, false, 25819, 4004, string("riaolfhtiyakmycpnyzwqqcwokybhzrtzjobcepvkpgyxyzxcnwsuuecpucehyrnicknzmmzsqlmeeddfhh"), 1180);
this->ydrgazrdytpslr(9599, false, 17428, 25189, true, false);
this->bayzrwldjxicxobnozubyo(6216, 287, false, 2153, string("vgvzehwnbskljzvgwyhhrdlhyfccbgdvdpbljfnbqxzslntajohylgsguegoumgfjqukhkmuxxsxcdqcxbxa"));
this->vkduwnmasksalfjkixc(string("iijbzpffjmpiifp"), 40493, true, 72, 58138, true);
this->yiafosyqyovvzfmhwrvzk();
this->jfdkxexvigstiisvlkbo(4921, 50427, 1291, 28039);
this->lubskwwlktdxrwftnbfico(string("twtdpopreltbipjqqkgodtba"), string("vqfzeeaebbutayikfkjgvyaskwzvdpmegjwz"));
this->becwbdoodszruauqcjetqcm(string("hmcr"), 6168, false, 4684, 3565, string("huvrbpzcutpezxyscqbdszhlvgfynjsfsltkdndluxanoaatnwawppleskwoqpcalkbfabtigqyjdtfyoyujkaijaajrhkutxv"), false, false, true);
this->ofiltmzneankz(1805, string("dwdh"));
this->uhbwyduhvggcezmozjqu(6078, 30836);
this->htrxsxbixzyck(true, string("vwelzydwyadbmhlsjazhayvobuoxkyrohrvabclpaobcxdornfu"), string("dxcswdlnwtppqkidxhowkugtyquylcbjgfozrcoogqetgxcwcyegcsxzoqoojqgkwyiqdhrqajcoymiafdwldeb"), 34189, 1164, false);
this->libujmlbwk(string("ddlhbouclcvurzxspziilmesrvljwujtepgekdrhomtlosobsruodlwwfmsqgmq"), false, true, string("mcsfhccuytyweedqzveii"));
this->lwwphggngrnks(string("lhnvgdyu"), 33283, 9111, 24429, string("ogqdskmqyvekfzrwrbgcajetmpeutiukpovcjlxaijcqfuqnhlpwadmogeplkgxwwrutrnrfkfwyyrjrwawafa"), true);
this->gatjrtuvgssdrfetaykvkyybl(249, true, true);
this->ofqjilgubl(true);
this->ztebjyvqtdqx(925);
this->tzjgyhqgmarks();
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class uodmxeo {
public:
string iwfynbhlaas;
uodmxeo();
string zubtxozevlxoxkuc(bool rlrcfelmprxwyx, string ispgltkcnnux, double giohvcyewbkzv);
void qmyyqughorsqlprhizb(bool jxsrdfm, string ajzaowixdrcoyj, double vmlqbqntwlm, string nrfapbaootli, int tvietyzevdeco, bool cjwmjlclpz, int bgcpxhxzbnuwn, int rmzmeyswg, int hqftm);
void mzoujualacwwhzjswdc(string xrwmjtzvcy, int frwfmdmhgbeum, string epewun, string issoakhzeggs);
string gfvsqzclwsefdsmbijkllpqbu(string yevwumx, int znamaekhacqf, string egwmjtibux, string sywcjfq, int uvtvhgtafr, int tvbhthqlvv, bool gwdceze, string fljujrv);
bool udjnhmkwoocvqiququa(int foerav, bool pitsioublcnk, string tgzkekrfeqhhwqd, string iiaqhiiuoaaa, bool rdgyaripsraika, int szednexwaxuv, string tlflly, bool nlfkuqlqmho, string tcgkhrherzb);

protected:
string ruznvhcfmduuz;
double mvubrl;
string zgltuxcsc;

void zihnvsrhvmehmvhwbfovlkajh(bool rnlxoaodqjtdfm, bool nivulwriuueilz, string yhijutqxdcu, string fgiswksf, string dbdintdi, int nrohzqd);
string oojpgszcojuoaxnare(bool whafrnb);
string nnjrtcuxkiuhyohaoywhzox(double wvkgfhfmccsy, bool ifkujlock, double sfpqadb, bool awzohgremausaqa, bool nrqrsaqrewrbcvr, int jjrds, int wjiwbq);

private:
int vbmenqwlywz;
int fahqavhqjb;
int fkpvyweupvxff;

double giodgmiwfkaqeffqqgmyya(int alzylofjlnbt, bool onqqbdeeohwnjud, bool aivasijmrbnqfbb, string pfxbedrdcbbnzh, string hylqxyxufdqu, string xnnefuwqnt, double pizdfzayi);
string cftdmvkiftsezmrubvidvb(string fuopmm, bool yhgirewsrgn, string uejlhv);

};




double uodmxeo::giodgmiwfkaqeffqqgmyya(int alzylofjlnbt, bool onqqbdeeohwnjud, bool aivasijmrbnqfbb, string pfxbedrdcbbnzh, string hylqxyxufdqu, string xnnefuwqnt, double pizdfzayi) {
bool cxzctiiudjwdd = true;
double kegvjrlrki = 4049;
bool ycwxdqvhhfficd = true;
if (true == true) {
int fsonqhusx;
for (fsonqhusx=40; fsonqhusx > 0; fsonqhusx--) {
continue;
} 
}
if (true == true) {
int karxirgszp;
for (karxirgszp=55; karxirgszp > 0; karxirgszp--) {
continue;
} 
}
if (true != true) {
int xgmqturhyx;
for (xgmqturhyx=34; xgmqturhyx > 0; xgmqturhyx--) {
continue;
} 
}
if (true == true) {
int mfywt;
for (mfywt=79; mfywt > 0; mfywt--) {
continue;
} 
}
if (4049 == 4049) {
int mlpgkgqvb;
for (mlpgkgqvb=83; mlpgkgqvb > 0; mlpgkgqvb--) {
continue;
} 
}
return 89509;
}

string uodmxeo::cftdmvkiftsezmrubvidvb(string fuopmm, bool yhgirewsrgn, string uejlhv) {
bool xviazle = true;
string ribdl = "lkotxwxzqzfebkmaxrdirawpiadzjmkai";
int bvrwoonrfdpvn = 2019;
int edcwypwljl = 147;
int gfxpjm = 2515;
string xycmcjfls = "xllbwnvllgmrabaucbgbmf";
string oociuhnsadh = "pghxxzfiocpcurkxeqnthrjzhhwkrbauaxatawcjpyxqgyujqbupxgniritwxzlojjdxtgwfwsotbiazafwltheimchuotfig";
string rvdhvn = "eptksnfhozlhccfhsankhrkritswuvxmldvqjaz";
string rotbetlbhr = "fjaywatje";
bool vixhsorhcznzvtq = true;
if (2019 != 2019) {
int atour;
for (atour=19; atour > 0; atour--) {
continue;
} 
}
if (string("lkotxwxzqzfebkmaxrdirawpiadzjmkai") != string("lkotxwxzqzfebkmaxrdirawpiadzjmkai")) {
int ob;
for (ob=24; ob > 0; ob--) {
continue;
} 
}
if (147 == 147) {
int kebkymd;
for (kebkymd=8; kebkymd > 0; kebkymd--) {
continue;
} 
}
if (string("lkotxwxzqzfebkmaxrdirawpiadzjmkai") != string("lkotxwxzqzfebkmaxrdirawpiadzjmkai")) {
int jhnydfy;
for (jhnydfy=89; jhnydfy > 0; jhnydfy--) {
continue;
} 
}
if (string("pghxxzfiocpcurkxeqnthrjzhhwkrbauaxatawcjpyxqgyujqbupxgniritwxzlojjdxtgwfwsotbiazafwltheimchuotfig") != string("pghxxzfiocpcurkxeqnthrjzhhwkrbauaxatawcjpyxqgyujqbupxgniritwxzlojjdxtgwfwsotbiazafwltheimchuotfig")) {
int mqtwlo;
for (mqtwlo=40; mqtwlo > 0; mqtwlo--) {
continue;
} 
}
return string("jwxgaozkim");
}

void uodmxeo::zihnvsrhvmehmvhwbfovlkajh(bool rnlxoaodqjtdfm, bool nivulwriuueilz, string yhijutqxdcu, string fgiswksf, string dbdintdi, int nrohzqd) {
string lkddpfcwq = "ivzuooipjskizmmfynnrfpmaqjrdxhbtevehgqowxcfveh";
string mzhqoavzubtjrk = "wcclwgryirg";
if (string("wcclwgryirg") != string("wcclwgryirg")) {
int oaicjs;
for (oaicjs=57; oaicjs > 0; oaicjs--) {
continue;
} 
}
if (string("ivzuooipjskizmmfynnrfpmaqjrdxhbtevehgqowxcfveh") != string("ivzuooipjskizmmfynnrfpmaqjrdxhbtevehgqowxcfveh")) {
int hrlvbield;
for (hrlvbield=6; hrlvbield > 0; hrlvbield--) {
continue;
} 
}
if (string("ivzuooipjskizmmfynnrfpmaqjrdxhbtevehgqowxcfveh") != string("ivzuooipjskizmmfynnrfpmaqjrdxhbtevehgqowxcfveh")) {
int tzjtmwzkyc;
for (tzjtmwzkyc=38; tzjtmwzkyc > 0; tzjtmwzkyc--) {
continue;
} 
}
if (string("wcclwgryirg") == string("wcclwgryirg")) {
int yglarjjst;
for (yglarjjst=71; yglarjjst > 0; yglarjjst--) {
continue;
} 
}
if (string("ivzuooipjskizmmfynnrfpmaqjrdxhbtevehgqowxcfveh") == string("ivzuooipjskizmmfynnrfpmaqjrdxhbtevehgqowxcfveh")) {
int nd;
for (nd=23; nd > 0; nd--) {
continue;
} 
}

}

string uodmxeo::oojpgszcojuoaxnare(bool whafrnb) {
string qwqzkqmcvbz = "iznbgteuemfhbjmgqgoutzswzfjtqcxvbzdidqeemztudyvnauqvpmddpuukwlabxciylnaokthvorpgb";
double tsofp = 14072;
int ssihcsqqlr = 721;
double zyzzldoq = 17560;
int nfmcvahicucbx = 3255;
string fdyzdsqztbl = "fgz";
if (string("iznbgteuemfhbjmgqgoutzswzfjtqcxvbzdidqeemztudyvnauqvpmddpuukwlabxciylnaokthvorpgb") == string("iznbgteuemfhbjmgqgoutzswzfjtqcxvbzdidqeemztudyvnauqvpmddpuukwlabxciylnaokthvorpgb")) {
int wjyn;
for (wjyn=85; wjyn > 0; wjyn--) {
continue;
} 
}
return string("olgus");
}

string uodmxeo::nnjrtcuxkiuhyohaoywhzox(double wvkgfhfmccsy, bool ifkujlock, double sfpqadb, bool awzohgremausaqa, bool nrqrsaqrewrbcvr, int jjrds, int wjiwbq) {
bool tlccnyypocqsy = true;
int pfyxtwngiviuji = 4303;
return string("xurcpqpuxhfalgssea");
}

string uodmxeo::zubtxozevlxoxkuc(bool rlrcfelmprxwyx, string ispgltkcnnux, double giohvcyewbkzv) {
string uljchwdnouixm = "edepdfxpvfzglicljdcylozqvcwstrimoogwcfr";
bool lmvvlklzpxctt = false;
double ntymcqw = 5534;
bool iwdcfmgvqvhofw = true;
bool hxjswmsesnqp = false;
double lpcwuobitwl = 34085;
int gdqfjt = 1955;
double ezobmvtu = 8616;
string ddqmgkaxyfi = "hiz";
if (false == false) {
int lxoxinrr;
for (lxoxinrr=52; lxoxinrr > 0; lxoxinrr--) {
continue;
} 
}
return string("bdzbljjpyshwhtg");
}

void uodmxeo::qmyyqughorsqlprhizb(bool jxsrdfm, string ajzaowixdrcoyj, double vmlqbqntwlm, string nrfapbaootli, int tvietyzevdeco, bool cjwmjlclpz, int bgcpxhxzbnuwn, int rmzmeyswg, int hqftm) {
string qhymgdkseldm = "xvraxoigkutgqgvotupuhorefzdnsrozdxrvqvhzp";
double irwdfvnen = 75863;
bool axyloox = false;
bool iqmbh = false;
double uqcqifbpiv = 22798;
double towotvieiq = 35575;
double xkdpetrwzcyya = 10707;
if (10707 != 10707) {
int eonscj;
for (eonscj=55; eonscj > 0; eonscj--) {
continue;
} 
}

}

void uodmxeo::mzoujualacwwhzjswdc(string xrwmjtzvcy, int frwfmdmhgbeum, string epewun, string issoakhzeggs) {
string qojeaxujezy = "ueyhsmdnafyjowraztyonty";
double expgp = 15105;
bool vfbdjm = true;
bool dyzidkyztdyco = true;
bool wvdvtdsg = false;
if (true != true) {
int zqz;
for (zqz=5; zqz > 0; zqz--) {
continue;
} 
}

}

string uodmxeo::gfvsqzclwsefdsmbijkllpqbu(string yevwumx, int znamaekhacqf, string egwmjtibux, string sywcjfq, int uvtvhgtafr, int tvbhthqlvv, bool gwdceze, string fljujrv) {
string bkvsvi = "uxienkzkhbjvyxwrurowvfywnmysrcadaxrluoxgkpmqsslkulowfpluzecxdbvawrxbdibnelcnwnyhmslfhuulqndu";
int smjaytanqqgiu = 4329;
double mctqmhvfpcuhj = 41763;
bool miitprgvhoanox = false;
bool rugxttawxub = true;
bool jhpfbagay = false;
if (false != false) {
int ayoqfje;
for (ayoqfje=40; ayoqfje > 0; ayoqfje--) {
continue;
} 
}
return string("");
}

bool uodmxeo::udjnhmkwoocvqiququa(int foerav, bool pitsioublcnk, string tgzkekrfeqhhwqd, string iiaqhiiuoaaa, bool rdgyaripsraika, int szednexwaxuv, string tlflly, bool nlfkuqlqmho, string tcgkhrherzb) {
int opduwsciviqjmdx = 4915;
double osvohdhbuwibvs = 4867;
string kzelwufasynir = "ybgszlvhubsosvfcvjulbxleiozcfiemjmactnevcaqdokuqdbmr";
double rxujpwnbhefrtwz = 12737;
double zidchd = 10595;
bool lmpsar = false;
return true;
}

uodmxeo::uodmxeo() {
this->zubtxozevlxoxkuc(true, string("grjemblpu"), 13242);
this->qmyyqughorsqlprhizb(false, string("wdzutssrixsyzickpfrmlicveasxugaylffncxdgsrcxgmfbuhjqxqiysauskhsuhitsyx"), 73199, string("rbipjmjddshocyumjegbkifbdombvnwrlhkawpbeezxfayygphgjankwldxt"), 100, true, 839, 4818, 3858);
this->mzoujualacwwhzjswdc(string("ubpzxwutawllkmwngbdcjsoyjorahjbsbpaeikqgysdeadnohmbfpaudq"), 3122, string("eemdxxumakycizvupbyzfblwnrdmfiwzhmxyfwbvidikmhazaywccjnkokmbaiuhegliokhodzweamrjwrypezghgrqetswpvq"), string("vbrcfzxmkxtfmrlpcuoqcvfunqahl"));
this->gfvsqzclwsefdsmbijkllpqbu(string("eadaxiglsvtymscyhtskxzymefztlycykaewlzrlegsmhgpjvibkaxgobhvfkdkrqnyks"), 4257, string("penfggiwrhgkfxxrvhuvouowkkwfweovqgtduvwfkfrptkmcpsmdwffguivqjvicxfdkbercdu"), string("fhxapwmjwqwffjnvyeztphzktntrlgydpsr"), 830, 5800, true, string("dxoslysmhlcdbesnuywfbaazflrywvuuzrgkwntrmmtamhzpmjiieeg"));
this->udjnhmkwoocvqiququa(1414, false, string("wbwswyixvkkkpzgoewijcrbhrnsqfcbfopxfgyzqthlmackwjg"), string("fncccfcmbyoazhtyemmql"), true, 2057, string("uasjruldwvqdaijiozvppughzqzaoziivg"), true, string("zldgj"));
this->zihnvsrhvmehmvhwbfovlkajh(false, false, string("cufcsoupmwytxqeqzttfvbuboypqwfwhszkummlqnntxxflwxckwewphrilaogpjrxivfqroqtuikekebxwsbwlazutv"), string("fdxqoljbfpvrepyqzprgqdylmlckckfvymlbsteevowjekchnakknsyykbdckizpwjvprwynfoqgqescemvmvwfuizan"), string("domgaczvuuunytqwoihvngkkzbjqaukvhfifrkqtpuxivwoomdiksrpywudaoofurtapmymglxzdyuezvy"), 105);
this->oojpgszcojuoaxnare(true);
this->nnjrtcuxkiuhyohaoywhzox(79395, false, 14216, true, false, 2903, 2792);
this->giodgmiwfkaqeffqqgmyya(1437, true, true, string("lhkqaddknic"), string("piybrokwxdnuzgnwuhzavnxpfhzjuahdghkozmbyrrsgt"), string("ppttztpalamfhuukoxmjjeorxjngcworledyfvmsdawsouzwwvqjxzget"), 6740);
this->cftdmvkiftsezmrubvidvb(string("e"), false, string("njhzmwwubkfxtqltbwyrthhjhfyeododjudushfvxbsxgkeorcskloqcuralzrdulgxxdruszfwnesgdiqssaogjchuuumec"));
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class htbvycb {
public:
double fotcn;
htbvycb();
double cruajikgccjkgwtrlqcue(double xkyhlxooeed, bool ndznatmwt, string xkvjrzkjsnwi, string jeeqq, int hoorabt, string zsvbcchxamszu, bool ocanadlxxg, bool ycycm, bool fjcphouapll, string jfxdvriw);
bool mgzhigsmalesqzyehtvv(bool ciftipgegua, int omyzmjec, bool atnuyeigk, bool kxxlbd, int enhkkir, string cwylnwqxt, string zvterlyromn, string jgvzycy);
bool wonsxzynmiifoufy(double gavboaxoc, int wjevoexgdluqzpe, string zxqqhxafu);
double xgfolniyjhdw(string mtsya, double xuvmvyysyvdu, string rialbmlmyoyw, string sparsvfm, string xjenqusgbhtd, string ljcfjdzsrojvah, double rlhicqttb, double jzqezc, int gfphyaey, bool movfzriyrgnz);
double ujhdhdokpjqnpzna(int ugarirrto, double hfkzwlqr, string dgaqcpoya, bool pfiyxfpbobb, int vrmgabkhdvebaan, int ocmjcflftymnaa, string ighszydig, int ccsekjv, bool zhnccm, string dobqcz);
void aysvjsncrmluepgplyvfc(string xppfkygvwkkx, double yjzlzzuzj, string ocymssfaqnsr, string mjmlpivxb, int npjgxfng, bool jizvdegyfvzasy, bool swapexpajqqjmdg, string nczimxvvbw, bool kfjpsukvxvcy, double vljahpgogckwv);
int adglehbljnbrwkbswtznv(string hjayqdnek, bool drsoafrx);
void jicequewoldjolunhywvxuiv(double svnkwdxfiswy, string otwopy, bool mqzvnft, double ifmwiuq, string sjryjrft, bool souzzsvaszytiv, string uexdswpe, bool dxhxtilphyplwvr, int lqvexfwihftrk, bool feyehhtdeh);
void xugxtbfgqdzxkwdr();
void othkhzdonzzzizr(string odbfvokgmbbfzyb);

protected:
double ggbbdsszpgcpe;
int rvzdonqndhqozbh;

string iyfrlisvmruuwrr(string nydol, double ydkkflj, string oxsktpn, double kmkqycbscbg, string jowipkleasodksy, int zfaffgjqmcc, bool ptzgtyhrzwcqg, string qjnkpdspuqzqnro, double zwsegrtd, string tnudrkcqp);
void jnabnjgxhhygfuvelc(int inhkq);
int rvqbkryobdjud(int juxejam, double pbpbsjruk, double gzxpmwytptj, bool fcnrwxfvocumxag, bool wdckrapx, double gwgwoncmuqaw, bool gofygdqevyov, string stqtt, double tgtrbgobqy);
bool taecazmtelu();
string zqqgbfadwomxybgseikcawaxb(int igkcvhk, int swlmvirscuw);

private:
double juklhqx;
double ugqekdnyydaxh;
string hooacbmvpgyzw;

void rbacgqbyguurdrxaxwpcekri(bool hkmtwehnco, int mspsbfhlyyqza, int cmmpf, string jfbdzc, bool jzkwl);
bool gdtmfsojjzpctsarobx(double cmabcygsqqp);
void xeevgqkpadiamzfffx(bool asscazfcloomxgv, double amrwbtpfmkar, double vkqytkg, int cursfavzgxvrm, int sbkibz, double ntzvvw, bool ukmmqklprxucvk);
string krosiqejbbrgdjuzagogquka();
void dhctjcpljpji(int wdorbnzjlmhhua, int rdkhbydvkzwjq, string jrirno, int hdblhm, double ntzlzjfawmgxkc);
int xqjwwyxahlpeovhqvrpa(double vbjzvct, int arfendyei, string cabfrynghm, bool ltwedoo, bool qzqgkgkflk, string cyzvdc, string ktoqcaxsophc, bool vnorcyyhbbrc);

};




void htbvycb::rbacgqbyguurdrxaxwpcekri(bool hkmtwehnco, int mspsbfhlyyqza, int cmmpf, string jfbdzc, bool jzkwl) {
double qrplkdnqrvrgnt = 95187;
bool dtpsavjy = true;
bool nygwmyndaoiiw = false;
double ahirmdcpgscd = 6406;
int bcjipnfuclghtn = 68;
double bufae = 2322;
double djvvalebsi = 9182;
string cllifcdxohu = "bjewpkwtgbgtzfugagezsiaxktmsqfbdcgnqjdgsthjw";
int xyyntcgvgkfweh = 3209;
int wswts = 8026;
if (false != false) {
int no;
for (no=53; no > 0; no--) {
continue;
} 
}
if (false != false) {
int qpi;
for (qpi=45; qpi > 0; qpi--) {
continue;
} 
}
if (string("bjewpkwtgbgtzfugagezsiaxktmsqfbdcgnqjdgsthjw") == string("bjewpkwtgbgtzfugagezsiaxktmsqfbdcgnqjdgsthjw")) {
int nbvqqefawr;
for (nbvqqefawr=95; nbvqqefawr > 0; nbvqqefawr--) {
continue;
} 
}

}

bool htbvycb::gdtmfsojjzpctsarobx(double cmabcygsqqp) {
string cpfsaqaymotr = "eqjqisxfbuzlrwxqwhcmnysbqsohufikhmoncczpuinwtol";
string vrfxcapump = "mknndjxrssjvlykltqzcihrqikdsznljcnitlrqqrbuprwccoeddhntsdmhkptsmtexghtnpljgss";
double qyrdhqymaxyha = 6903;
if (string("mknndjxrssjvlykltqzcihrqikdsznljcnitlrqqrbuprwccoeddhntsdmhkptsmtexghtnpljgss") == string("mknndjxrssjvlykltqzcihrqikdsznljcnitlrqqrbuprwccoeddhntsdmhkptsmtexghtnpljgss")) {
int uku;
for (uku=0; uku > 0; uku--) {
continue;
} 
}
return false;
}

void htbvycb::xeevgqkpadiamzfffx(bool asscazfcloomxgv, double amrwbtpfmkar, double vkqytkg, int cursfavzgxvrm, int sbkibz, double ntzvvw, bool ukmmqklprxucvk) {

}

string htbvycb::krosiqejbbrgdjuzagogquka() {
int gysqagocqx = 304;
string nidtlufpdvdmwm = "jlldlpjhdcoucaygbfcasfsoudhkkgudxoblbyrbevkodseiiugpdczigfxxdbxldqqnvccrdvoajshogxxipspchgeaeexhgt";
bool luysrsuo = true;
bool qznszgrko = false;
bool qlhwn = true;
bool rbunflpfwnbhn = false;
double dxtxakbcuyn = 15843;
if (false == false) {
int afzumvgxfr;
for (afzumvgxfr=92; afzumvgxfr > 0; afzumvgxfr--) {
continue;
} 
}
if (15843 == 15843) {
int ymtj;
for (ymtj=18; ymtj > 0; ymtj--) {
continue;
} 
}
if (false != false) {
int cjedzjhq;
for (cjedzjhq=57; cjedzjhq > 0; cjedzjhq--) {
continue;
} 
}
if (string("jlldlpjhdcoucaygbfcasfsoudhkkgudxoblbyrbevkodseiiugpdczigfxxdbxldqqnvccrdvoajshogxxipspchgeaeexhgt") == string("jlldlpjhdcoucaygbfcasfsoudhkkgudxoblbyrbevkodseiiugpdczigfxxdbxldqqnvccrdvoajshogxxipspchgeaeexhgt")) {
int ppchr;
for (ppchr=69; ppchr > 0; ppchr--) {
continue;
} 
}
return string("e");
}

void htbvycb::dhctjcpljpji(int wdorbnzjlmhhua, int rdkhbydvkzwjq, string jrirno, int hdblhm, double ntzlzjfawmgxkc) {
string urhmqsbqczczib = "znuvcgicwityngzukjyhccsuymyhqguztdoclso";
bool orrfumbjrsy = true;
if (true != true) {
int rjkrngifre;
for (rjkrngifre=61; rjkrngifre > 0; rjkrngifre--) {
continue;
} 
}
if (string("znuvcgicwityngzukjyhccsuymyhqguztdoclso") == string("znuvcgicwityngzukjyhccsuymyhqguztdoclso")) {
int kvetixe;
for (kvetixe=84; kvetixe > 0; kvetixe--) {
continue;
} 
}
if (true == true) {
int bf;
for (bf=8; bf > 0; bf--) {
continue;
} 
}
if (true != true) {
int vx;
for (vx=10; vx > 0; vx--) {
continue;
} 
}

}

int htbvycb::xqjwwyxahlpeovhqvrpa(double vbjzvct, int arfendyei, string cabfrynghm, bool ltwedoo, bool qzqgkgkflk, string cyzvdc, string ktoqcaxsophc, bool vnorcyyhbbrc) {
string bbkmlljmylto = "msacjedvsamfoaggrapbhcpeesrrzgnhabvacqxfoyhraxkkrbvhcdpfz";
double lxodauzvyuy = 6789;
double pwwfhjb = 13324;
int oojwgz = 718;
return 70255;
}

string htbvycb::iyfrlisvmruuwrr(string nydol, double ydkkflj, string oxsktpn, double kmkqycbscbg, string jowipkleasodksy, int zfaffgjqmcc, bool ptzgtyhrzwcqg, string qjnkpdspuqzqnro, double zwsegrtd, string tnudrkcqp) {
return string("xblgcmwvtwshploaut");
}

void htbvycb::jnabnjgxhhygfuvelc(int inhkq) {
string eviyjiigdcf = "lrgxlkpnlzcxssauaykpkyijegouzrygesgegyzevzfhxhsrmdoxayafzivykxloepljnnxdzdtarvjawzuvqvpx";
double jsoyeay = 16070;
double fumdlgjpahcb = 33536;
string fbnkaiy = "bnicfefeqptvypettkktes";
string azzqzyfabgqto = "rxzbxyyigpvjv";
double glgtltggrhwjmv = 33561;
bool hlepg = false;
bool ilyvionxnutyoe = true;
int ypzsszvrghpuf = 2058;

}

int htbvycb::rvqbkryobdjud(int juxejam, double pbpbsjruk, double gzxpmwytptj, bool fcnrwxfvocumxag, bool wdckrapx, double gwgwoncmuqaw, bool gofygdqevyov, string stqtt, double tgtrbgobqy) {
bool fedpekdqfsxm = true;
string oqnxuv = "zdbgynoanwmrwilbiadoyxulsssmdorqzzqswhougythelq";
if (true != true) {
int lhwl;
for (lhwl=14; lhwl > 0; lhwl--) {
continue;
} 
}
return 87586;
}

bool htbvycb::taecazmtelu() {
bool vikzlk = false;
string youwlsraxcabqa = "dhivtijmdpuvdyxbmhfhvhdzpnekvtoxj";
double lqpeef = 22546;
string mlhvpopblxqlv = "xajdoyahzggmf";
bool tmchvntcstyruxl = false;
int urmffr = 6269;
if (string("dhivtijmdpuvdyxbmhfhvhdzpnekvtoxj") != string("dhivtijmdpuvdyxbmhfhvhdzpnekvtoxj")) {
int bkkk;
for (bkkk=50; bkkk > 0; bkkk--) {
continue;
} 
}
return true;
}

string htbvycb::zqqgbfadwomxybgseikcawaxb(int igkcvhk, int swlmvirscuw) {
int digzx = 9009;
string fzmagyx = "iqzkcyvwncyjmcvvddpezmzdwuamlsz";
double lgunxwkoilk = 68778;
string hhhmyyoeym = "cypgxsatkdzvonabteynftwesjrhxkktnolgwibbecedeoaviaurojycusnqsgrxhneuzoeplwmxeeauaotokso";
int qpvzowothgowmv = 4426;
if (9009 == 9009) {
int lpagqkndb;
for (lpagqkndb=70; lpagqkndb > 0; lpagqkndb--) {
continue;
} 
}
if (string("iqzkcyvwncyjmcvvddpezmzdwuamlsz") == string("iqzkcyvwncyjmcvvddpezmzdwuamlsz")) {
int yrdeg;
for (yrdeg=55; yrdeg > 0; yrdeg--) {
continue;
} 
}
if (4426 != 4426) {
int flqmyxh;
for (flqmyxh=36; flqmyxh > 0; flqmyxh--) {
continue;
} 
}
if (4426 == 4426) {
int qlqqxklay;
for (qlqqxklay=44; qlqqxklay > 0; qlqqxklay--) {
continue;
} 
}
return string("pee");
}

double htbvycb::cruajikgccjkgwtrlqcue(double xkyhlxooeed, bool ndznatmwt, string xkvjrzkjsnwi, string jeeqq, int hoorabt, string zsvbcchxamszu, bool ocanadlxxg, bool ycycm, bool fjcphouapll, string jfxdvriw) {
bool wdefh = true;
bool ygprouazx = false;
bool bdqzsyb = false;
double gexpw = 53251;
string fgdlzud = "qlngmokjiiguqvdrbgqtczbsuwqwpcsxhnryrqve";
if (true != true) {
int ykls;
for (ykls=41; ykls > 0; ykls--) {
continue;
} 
}
if (false != false) {
int xf;
for (xf=30; xf > 0; xf--) {
continue;
} 
}
if (string("qlngmokjiiguqvdrbgqtczbsuwqwpcsxhnryrqve") != string("qlngmokjiiguqvdrbgqtczbsuwqwpcsxhnryrqve")) {
int jtospquiv;
for (jtospquiv=0; jtospquiv > 0; jtospquiv--) {
continue;
} 
}
if (false == false) {
int bks;
for (bks=58; bks > 0; bks--) {
continue;
} 
}
if (false == false) {
int txhdjxpun;
for (txhdjxpun=43; txhdjxpun > 0; txhdjxpun--) {
continue;
} 
}
return 2951;
}

bool htbvycb::mgzhigsmalesqzyehtvv(bool ciftipgegua, int omyzmjec, bool atnuyeigk, bool kxxlbd, int enhkkir, string cwylnwqxt, string zvterlyromn, string jgvzycy) {
string wxdlodogquvinvz = "nxsbkzbzwlapbniwkhlpatyrjiitgvilapjyxxfuzvbbvtiutexpneacdlqyflndzlu";
string ktgoz = "oclnaxhskdudwntbzanbyqsmupcvmpfknjttbetjkygxjwyioafvwknvxndbmtnfrg";
int fyspliiqioi = 5532;
double yhryuk = 10980;
int utknxkhguu = 1745;
bool emtrhtxoyocxn = false;
bool avqlvaxp = true;
if (5532 != 5532) {
int ilbpoowltv;
for (ilbpoowltv=38; ilbpoowltv > 0; ilbpoowltv--) {
continue;
} 
}
if (string("nxsbkzbzwlapbniwkhlpatyrjiitgvilapjyxxfuzvbbvtiutexpneacdlqyflndzlu") == string("nxsbkzbzwlapbniwkhlpatyrjiitgvilapjyxxfuzvbbvtiutexpneacdlqyflndzlu")) {
int alxqbvk;
for (alxqbvk=68; alxqbvk > 0; alxqbvk--) {
continue;
} 
}
if (1745 == 1745) {
int lvxi;
for (lvxi=84; lvxi > 0; lvxi--) {
continue;
} 
}
if (string("nxsbkzbzwlapbniwkhlpatyrjiitgvilapjyxxfuzvbbvtiutexpneacdlqyflndzlu") == string("nxsbkzbzwlapbniwkhlpatyrjiitgvilapjyxxfuzvbbvtiutexpneacdlqyflndzlu")) {
int ow;
for (ow=47; ow > 0; ow--) {
continue;
} 
}
if (5532 == 5532) {
int bsnnjrk;
for (bsnnjrk=16; bsnnjrk > 0; bsnnjrk--) {
continue;
} 
}
return false;
}

bool htbvycb::wonsxzynmiifoufy(double gavboaxoc, int wjevoexgdluqzpe, string zxqqhxafu) {
bool dfgwegsdsitxhl = true;
bool csstywxhezb = false;
double mkgnxjtvmwsatcn = 81669;
double fqandxupcf = 9479;
bool mpseorpzbqvppwr = false;
string rwrqzbkaas = "umebnvjdkjnrdtjwhhkserqnwxskidgxfmmkrdgalduplmaimyybvnlkoqifafgfm";
int btocdedknr = 43;
int phfkfjkkmc = 2112;
return true;
}

double htbvycb::xgfolniyjhdw(string mtsya, double xuvmvyysyvdu, string rialbmlmyoyw, string sparsvfm, string xjenqusgbhtd, string ljcfjdzsrojvah, double rlhicqttb, double jzqezc, int gfphyaey, bool movfzriyrgnz) {
bool iwjgwkunfeh = true;
if (true == true) {
int uey;
for (uey=75; uey > 0; uey--) {
continue;
} 
}
if (true == true) {
int lcexdh;
for (lcexdh=36; lcexdh > 0; lcexdh--) {
continue;
} 
}
if (true != true) {
int mtbvpzggyk;
for (mtbvpzggyk=23; mtbvpzggyk > 0; mtbvpzggyk--) {
continue;
} 
}
if (true != true) {
int fdyrwnfnbr;
for (fdyrwnfnbr=75; fdyrwnfnbr > 0; fdyrwnfnbr--) {
continue;
} 
}
if (true == true) {
int hckxigmzh;
for (hckxigmzh=81; hckxigmzh > 0; hckxigmzh--) {
continue;
} 
}
return 97973;
}

double htbvycb::ujhdhdokpjqnpzna(int ugarirrto, double hfkzwlqr, string dgaqcpoya, bool pfiyxfpbobb, int vrmgabkhdvebaan, int ocmjcflftymnaa, string ighszydig, int ccsekjv, bool zhnccm, string dobqcz) {
string ytqrnpwnl = "lmnrvmlgolwhhkymwnpxfsudnu";
if (string("lmnrvmlgolwhhkymwnpxfsudnu") == string("lmnrvmlgolwhhkymwnpxfsudnu")) {
int gwep;
for (gwep=14; gwep > 0; gwep--) {
continue;
} 
}
if (string("lmnrvmlgolwhhkymwnpxfsudnu") != string("lmnrvmlgolwhhkymwnpxfsudnu")) {
int afehtwipp;
for (afehtwipp=8; afehtwipp > 0; afehtwipp--) {
continue;
} 
}
return 39718;
}

void htbvycb::aysvjsncrmluepgplyvfc(string xppfkygvwkkx, double yjzlzzuzj, string ocymssfaqnsr, string mjmlpivxb, int npjgxfng, bool jizvdegyfvzasy, bool swapexpajqqjmdg, string nczimxvvbw, bool kfjpsukvxvcy, double vljahpgogckwv) {
int rsmdxm = 2246;
double jjavsd = 53688;
int xtpqtxumdu = 987;
string wgfxxeyxvteip = "";
string fafvvssq = "vgeckqtdvcugnmbvwmdovwptgomivgpkzkqdjqaypzcjbgtccqmugvwknbujqgnngrcrquamlpvdyjbsi";
bool lglojlpk = true;
int jzyfltiez = 3226;
double lunwvtrutmg = 55214;
if (55214 == 55214) {
int sk;
for (sk=86; sk > 0; sk--) {
continue;
} 
}
if (3226 == 3226) {
int luryfpp;
for (luryfpp=75; luryfpp > 0; luryfpp--) {
continue;
} 
}
if (true == true) {
int iyozfkdzuz;
for (iyozfkdzuz=79; iyozfkdzuz > 0; iyozfkdzuz--) {
continue;
} 
}
if (string("") == string("")) {
int jkerl;
for (jkerl=91; jkerl > 0; jkerl--) {
continue;
} 
}
if (987 == 987) {
int xdia;
for (xdia=98; xdia > 0; xdia--) {
continue;
} 
}

}

int htbvycb::adglehbljnbrwkbswtznv(string hjayqdnek, bool drsoafrx) {
double wrupesfus = 49999;
string iueivps = "yucmvonfbcd";
bool arsefnkd = false;
string nbssyn = "zepgnfjbsejqhjjuudhqyanbdntemqjtgfextfustlqzzpzfotoztljlp";
int zzekywxsevpyp = 801;
if (false == false) {
int rzvws;
for (rzvws=34; rzvws > 0; rzvws--) {
continue;
} 
}
if (49999 == 49999) {
int adxu;
for (adxu=54; adxu > 0; adxu--) {
continue;
} 
}
return 716;
}

void htbvycb::jicequewoldjolunhywvxuiv(double svnkwdxfiswy, string otwopy, bool mqzvnft, double ifmwiuq, string sjryjrft, bool souzzsvaszytiv, string uexdswpe, bool dxhxtilphyplwvr, int lqvexfwihftrk, bool feyehhtdeh) {
int juczp = 1152;
double sqntblwxg = 16782;
int jghuxtojo = 1765;
int spnccbpllpdurz = 5548;
int zfoqeha = 6571;
double vgbyacwjrrbpyf = 19405;
bool xvppeghvmm = true;
if (19405 != 19405) {
int fkeh;
for (fkeh=86; fkeh > 0; fkeh--) {
continue;
} 
}
if (16782 == 16782) {
int snpij;
for (snpij=24; snpij > 0; snpij--) {
continue;
} 
}
if (16782 != 16782) {
int xopi;
for (xopi=38; xopi > 0; xopi--) {
continue;
} 
}

}

void htbvycb::xugxtbfgqdzxkwdr() {

}

void htbvycb::othkhzdonzzzizr(string odbfvokgmbbfzyb) {
int rhvtcuzmjq = 1670;
string bvoghblraqnh = "dlhdynbaawfjwwtyojgippcktowofvczbosmyrnrlcinvqngbwogpvdkwezqtxtlytwabmak";
string cwzuyjrq = "nhhyjkwncozgousuaizohctxejarcauyrqzeqdsfxhqnxxz";
if (string("nhhyjkwncozgousuaizohctxejarcauyrqzeqdsfxhqnxxz") == string("nhhyjkwncozgousuaizohctxejarcauyrqzeqdsfxhqnxxz")) {
int dzbo;
for (dzbo=28; dzbo > 0; dzbo--) {
continue;
} 
}

}

htbvycb::htbvycb() {
this->cruajikgccjkgwtrlqcue(19227, true, string("mgwzwfkrwoblkmjttwfavowzpjdrbhiwdyqfqhjxulbqoehulhalmvbroqhqdzsanpslzv"), string("wjmrfrmnujobonqbkjgekytqeqdodmekrwzulcxicihaddzlrjmfehtdlmsikzxbvqpoqajrauodzynucy"), 3659, string("krjoccddftvhidhaduptqcwghgfnzfcepcjjljgdjpkklwidblhraxmgsmfatjfhvbygrugugdhkqunvhsahpxisvcgfkxaevg"), true, true, true, string("azljngfyscgdtjekwufgbrgzmgsoizkwolsuavsvitrmktpqizuxha"));
this->mgzhigsmalesqzyehtvv(true, 491, true, true, 3605, string("ioydxx"), string("oekhrjahwofudajcdixczsprdfpmpxgecusnpkuqnacpqvhsmbdemnbqohkrpwablnocieldpiufazaljihrcfjo"), string("nhgwjcnpphwqbcvfyrxtvfnqtdcfoqyeazvx"));
this->wonsxzynmiifoufy(31681, 523, string("beqhdgoan"));
this->xgfolniyjhdw(string("inbwngfj"), 15890, string("ptjutwukmjdbkcsabxqjraubiyuxoxlpopso"), string("lqrcoxwevigborthjdasbexrxwryflzhtizeaudqscdrxqnzkuu"), string("rmpbmtlwpwycaul"), string("simozqnpjudji"), 19253, 30830, 184, true);
this->ujhdhdokpjqnpzna(1491, 25717, string("dlajhshuffrlurzeiopdsgorkggixiccllvbxtviiqkxhnmlnijmrx"), true, 1294, 975, string("ysxxrvbxbtknofpxvkfturwnnrmoqkfhgogdyofotefbhiqocoxincyon"), 230, false, string("qvvyhgayuzpdgivbsgtebybcvqareaesdxrgjlhixmocmufleraxqwgvzjpdeukinatazecw"));
this->aysvjsncrmluepgplyvfc(string("dcofwytigucqjbfbfulwbljfrtdddqjjczecyygpgdmapomhbdvqpeuetycxcqimm"), 33409, string("tbvzxirefrgvhsyohxrejmqukleqpatfymvmxyapulqxpgqbjxsluqzystdkgqpghkeooqteqxnvxbzhegzqucpbqvcwupwjvga"), string("hnauqbaeyubweuchwbelsqiqaozblgxdtzpozyxkcyldwmvdqmfvxzhmxcypzgoqqibyphcsfdddjygnkb"), 1678, true, false, string("sj"), false, 5675);
this->adglehbljnbrwkbswtznv(string("szkzecavurjqisbvjjaxjvhymtukokroadtxugkdindablsqojgbrsfhogliayzhaqjqbnxmiochwts"), true);
this->jicequewoldjolunhywvxuiv(22164, string("qlsspehptwsqhfcbtkidlqnxrlydbqjpkoymsobzfhppjuulqplklslrurh"), false, 19645, string("zrqmdimcxpluvpyhqdwrrysfiexdetazfzlmllrzajqqdsziltogiakqavsigxkvkhtbjedbxmevgywyrrwe"), false, string("mqkfyvzoibqsamkwpyqifsjutqcwleelaxdnhmocrrdlwvesrytnmuhtnmerhfierixxgmlrsnhoisppljqpzmnhuu"), true, 296, false);
this->xugxtbfgqdzxkwdr();
this->othkhzdonzzzizr(string("zchwlxpkqttsjiqitldxiaxz"));
this->iyfrlisvmruuwrr(string("eupaglknfvdsqlklpgdsesnkosk"), 21051, string("yqhyhicgqrzkbzfmefpzxm"), 33721, string("bl"), 2467, false, string("akcilpuoblzaldzjonzjkdwciqfwxtvwdtlb"), 34431, string("ywairsamrdblozsjaprhxgc"));
this->jnabnjgxhhygfuvelc(5742);
this->rvqbkryobdjud(123, 15302, 19426, false, false, 43346, false, string("jrymldybvsgtumgqbdumvxnlnnqghyr"), 61895);
this->taecazmtelu();
this->zqqgbfadwomxybgseikcawaxb(3634, 183);
this->rbacgqbyguurdrxaxwpcekri(false, 2440, 612, string("ozwwhxyfxeavbffdljrtalzguhekxdmsqhjewljlkuynwrsvgwyanporaaazgqhxvgzyqhtdyjoxvhriqnjuzycwlnox"), true);
this->gdtmfsojjzpctsarobx(86010);
this->xeevgqkpadiamzfffx(false, 25801, 31469, 4525, 2943, 82755, true);
this->krosiqejbbrgdjuzagogquka();
this->dhctjcpljpji(4562, 1556, string("ncvzkqijyllsjzrmsapcfacucshampdhjllhfzcxxcioyecfxvyszwqcsfothlmwmppshdsnemwcxriqdgzgwdxra"), 2238, 55512);
this->xqjwwyxahlpeovhqvrpa(9272, 4792, string("echwtdxyewbqghnujrbvidvyvmfqzzcjhvvsaawagwdjbsvksuqruxihtmoomkmjphyvsavjhifraivqrkfarrbvxbpwmqi"), true, false, string("iqkjjqckbeupgldzdkqugxkgvnwztaqivpjlcjrrxcdofejggpjnjdw"), string(""), true);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ppvmivi {
public:
string hdvmnnebb;
bool xmnwbhr;
bool gxbgrbgu;
double uiyxpaavtxmlt;
double wxjxe;
ppvmivi();
double rshedmxcirivvu(int hiqyublh, double kxceojgnzxw, string fcurcwbgm, string oilrivl, string nltbgvrwawxn);

protected:
bool nhrcext;

int uvlsfzjqldifczvpbbsugel(double lvafhmkomxdaq, string yhfozv, int totch, string vkvvahykuipiol, string udvli, int wgtratghntshnk, string gusiacyqtk, int nyscxrnojx, int icimkigak, int hldrliwpepx);
string itketefceavleqqizqtcffn(int ktsslcaysqak);
void qdfskvqpponyzgwoufggp(bool zbprwwxqlsnf, double njrlkr);
void idglokpobsavwozdzpanwqf(bool kaarkmzi);
int uyaudqetqgkwgrkjtt(string nptyeqtejks, bool guacvgxjfs, bool zxkzj, bool vvwnrtu, string qrjjcwakskxgatm, double gtcccyhryyzlqbm, bool vlcztox, bool cibduczz, double nsddw);
int tpilktqebrslvpvqufifrx(double ccttitcxnfm, double vssudizpee, bool akxxaqrj, bool thakhmalnnv, bool ctdivasxwdu, string inrxgbldwd, double fegziqs, double vipklpmxqau, bool vsdecir, int zuttxjqcn);
double vdozajfztcemh(bool xnnhxkmuebnuqw, string ygeibvvrxxp);
void ojwjabcimu(bool yxlyvzxzfwe, double otygt, string stujczmsoo, int stjkxedrw, string nwsdycuw);

private:
bool geefehlesap;
string iubtohg;

double zuknkhqrhkxuljktpckpbpd(bool rzalwi, int bxtzlqa, int mvhjpnpxeusbgvo, int skdrbztjijyk, double swoku, int eqjowbshol);
string ablafauotvmckhessvp(string vznvt, int dfisaist, string guvdko, bool cabqku, bool xemivuvkseequb);
string uigkrfrkwhxtrejfwlcsc(double bepshufrirf, bool xyjfrad, string vssumiixiwvxtca, bool vvxkioawkkilv, string fgjjt, bool zbrqacr, string qagjhiukp, double qpizgxwvqjl, double lbyzauipvnztil, double opqgmfxfrz);
bool pgavwibftwzkt(int pkgcxhyimvhiwhs, double xmheg, int rgoyhx, double kivrpgvstayzv, bool obibfswbbobdnzy, double dxhabyqy, int dnqhzhfzpbc, string qsztnzmfylh, int exeagiakckphqxf);
string ocjgqdrthtyuubigfajbw(double eryveevs, double dltsunsccmqwkw, bool pddlcbzlqpxjnz, bool hkysllp, int pudbaauqzzf, int oubsxacefhhqi, string oqlwcsbrl, bool vserswqhlwy, int korvaerayaq, double nscbhvtfjc);
string qreikhlnlpjs(int onqxwbeystzfdnx, int yccxbyb, int czakbgfuyg, int lnwpiqhrllut, int audgaziivpv, double elifx);
int qvkzrzetybmohqfpt(int cpexv, int cgodbk);
void cjfnimpdcgi(string kyrzkpy, bool yunfxoixlbmrefu, string lyhnmr, double zhvqpncrjr);
double pvkjzbnhimhthtxdc(string epowvp, bool mztnhwptcon, double ufkoeljy, int ahbhyijuqvgnxru);
string mqbovmjfoeixmqnvr(string xvtcr, double raajdbkjjrz, int wxlecud, int uesgnfjgpd, string pnkxuxqt);

};




double ppvmivi::zuknkhqrhkxuljktpckpbpd(bool rzalwi, int bxtzlqa, int mvhjpnpxeusbgvo, int skdrbztjijyk, double swoku, int eqjowbshol) {
double gnbzys = 23616;
int hlsrf = 514;
double fzvjskwredkn = 18909;
int pdkensgjym = 1774;
int oegnzgypbgen = 228;
int yrlkmdr = 5516;
return 10465;
}

string ppvmivi::ablafauotvmckhessvp(string vznvt, int dfisaist, string guvdko, bool cabqku, bool xemivuvkseequb) {
string cwzwqybjhhi = "jklnsykhdvbfcnbsmqcjmcmpvmwovbtudlbfxbizrivvfpksrnpzgsirhqwdpkjrvwppzztrcwyswmscuteufz";
string krsnsidplzvfqa = "zdlxhnyupglhswghfsihvauuosfqdlcw";
bool kecxfw = false;
bool fkwgz = true;
int rhpgyuuuqpzsv = 5085;
bool kzkhsedsbw = true;
double isgtco = 8109;
int teulfczp = 733;
double fzjhgglzzxjqz = 43360;
double eozvpdzgoquw = 10033;
return string("nlwjjoekbupndaypogy");
}

string ppvmivi::uigkrfrkwhxtrejfwlcsc(double bepshufrirf, bool xyjfrad, string vssumiixiwvxtca, bool vvxkioawkkilv, string fgjjt, bool zbrqacr, string qagjhiukp, double qpizgxwvqjl, double lbyzauipvnztil, double opqgmfxfrz) {
string ymtapgxoxrksmo = "fmnerjjzylqipavuffmfgdsigllfjsu";
bool wmnedhpg = true;
int omyorv = 332;
bool tnsvfrbg = true;
int cegbydp = 72;
int pqtawbck = 7482;
int nqlcjjbbij = 335;
bool twxdae = false;
double uafngubxqcx = 13368;
string dnsuqas = "l";
if (7482 != 7482) {
int wiqpzqper;
for (wiqpzqper=50; wiqpzqper > 0; wiqpzqper--) {
continue;
} 
}
return string("olywtxeo");
}

bool ppvmivi::pgavwibftwzkt(int pkgcxhyimvhiwhs, double xmheg, int rgoyhx, double kivrpgvstayzv, bool obibfswbbobdnzy, double dxhabyqy, int dnqhzhfzpbc, string qsztnzmfylh, int exeagiakckphqxf) {
return true;
}

string ppvmivi::ocjgqdrthtyuubigfajbw(double eryveevs, double dltsunsccmqwkw, bool pddlcbzlqpxjnz, bool hkysllp, int pudbaauqzzf, int oubsxacefhhqi, string oqlwcsbrl, bool vserswqhlwy, int korvaerayaq, double nscbhvtfjc) {
int bdwzb = 6550;
double dcpkfjjzg = 9082;
string yyaltpbr = "qcpphwkysngefsahvmfpussalnyldfenajxwyetywhpofuxunmoziwqxpcqhgzgtmmyxklukqlhzlrne";
double guvkxbayaqtl = 56668;
string imzfmujie = "myflouamitjpbggsicqqjodgc";
int oybvdibubgwfuoj = 3316;
bool fexrcfam = false;
double wfwdav = 13712;
string rldwc = "aofyekullgqoarcwgwjawmhiaderxspzebdmcykseyblqnhfrcfycikuzucrynmjeohtcftgrlqfokmroaorvkny";
if (3316 == 3316) {
int fkrxvsydm;
for (fkrxvsydm=24; fkrxvsydm > 0; fkrxvsydm--) {
continue;
} 
}
if (string("qcpphwkysngefsahvmfpussalnyldfenajxwyetywhpofuxunmoziwqxpcqhgzgtmmyxklukqlhzlrne") != string("qcpphwkysngefsahvmfpussalnyldfenajxwyetywhpofuxunmoziwqxpcqhgzgtmmyxklukqlhzlrne")) {
int hcqtihpipj;
for (hcqtihpipj=64; hcqtihpipj > 0; hcqtihpipj--) {
continue;
} 
}
if (3316 == 3316) {
int qjugdqhy;
for (qjugdqhy=12; qjugdqhy > 0; qjugdqhy--) {
continue;
} 
}
if (13712 != 13712) {
int sygkcjgrj;
for (sygkcjgrj=2; sygkcjgrj > 0; sygkcjgrj--) {
continue;
} 
}
if (9082 == 9082) {
int ugiuokke;
for (ugiuokke=16; ugiuokke > 0; ugiuokke--) {
continue;
} 
}
return string("spvdp");
}

string ppvmivi::qreikhlnlpjs(int onqxwbeystzfdnx, int yccxbyb, int czakbgfuyg, int lnwpiqhrllut, int audgaziivpv, double elifx) {
double qvldzbvgqouztf = 8066;
double mzlxbube = 13225;
int nnmhqhypdvfsyyk = 7478;
if (13225 != 13225) {
int fr;
for (fr=33; fr > 0; fr--) {
continue;
} 
}
if (13225 == 13225) {
int rczqtwp;
for (rczqtwp=21; rczqtwp > 0; rczqtwp--) {
continue;
} 
}
return string("asvfiqeufmauyionyd");
}

int ppvmivi::qvkzrzetybmohqfpt(int cpexv, int cgodbk) {
double adzekvizwjqh = 8405;
bool dpppjjjqqymvat = false;
double ufspxrkr = 23379;
int thxeb = 3100;
double mbafvrrmefpyxyk = 9056;
string amlutvu = "nfnnxpdvtnrjqfmfqsdntqovnxb";
bool echmjsgzpguc = true;
bool zdorzoldmfwjb = true;
if (23379 == 23379) {
int jbanpzs;
for (jbanpzs=21; jbanpzs > 0; jbanpzs--) {
continue;
} 
}
if (23379 != 23379) {
int jq;
for (jq=95; jq > 0; jq--) {
continue;
} 
}
if (true == true) {
int qboxk;
for (qboxk=92; qboxk > 0; qboxk--) {
continue;
} 
}
if (9056 != 9056) {
int fgnfhm;
for (fgnfhm=98; fgnfhm > 0; fgnfhm--) {
continue;
} 
}
if (8405 != 8405) {
int qviity;
for (qviity=44; qviity > 0; qviity--) {
continue;
} 
}
return 98353;
}

void ppvmivi::cjfnimpdcgi(string kyrzkpy, bool yunfxoixlbmrefu, string lyhnmr, double zhvqpncrjr) {
double kagfmfoyldq = 69670;
int rqbanjsueho = 3460;
bool nbukfjuo = true;
int qrygsmbqhlmx = 415;
if (69670 == 69670) {
int lvyz;
for (lvyz=85; lvyz > 0; lvyz--) {
continue;
} 
}
if (415 != 415) {
int iqn;
for (iqn=24; iqn > 0; iqn--) {
continue;
} 
}
if (69670 == 69670) {
int stol;
for (stol=84; stol > 0; stol--) {
continue;
} 
}
if (415 != 415) {
int zilsw;
for (zilsw=50; zilsw > 0; zilsw--) {
continue;
} 
}
if (3460 == 3460) {
int tu;
for (tu=64; tu > 0; tu--) {
continue;
} 
}

}

double ppvmivi::pvkjzbnhimhthtxdc(string epowvp, bool mztnhwptcon, double ufkoeljy, int ahbhyijuqvgnxru) {
int cdjdgxtnh = 527;
int uwxqf = 2962;
bool whdbht = true;
int isfri = 101;
string bndmngcthl = "gavv";
string plmokdlsxbxrv = "gkqtvgsttympnszkebmbrnxgkzlatonbzvgxgcpaencwawufp";
string glvqedeh = "yhghambcvdievvaeco";
string wrmjflwsa = "sgpxroxkbzovbhnsedffdarzxlcczhekpdhhwalztlxiuqwkfwbadwulnkjgmzrvaxksmapnntieroeelgjvwnorvywmcq";
int zwcdawe = 966;
double horgjtbbf = 417;
if (417 == 417) {
int npbnhbfomt;
for (npbnhbfomt=38; npbnhbfomt > 0; npbnhbfomt--) {
continue;
} 
}
if (true != true) {
int pifuiui;
for (pifuiui=61; pifuiui > 0; pifuiui--) {
continue;
} 
}
return 58122;
}

string ppvmivi::mqbovmjfoeixmqnvr(string xvtcr, double raajdbkjjrz, int wxlecud, int uesgnfjgpd, string pnkxuxqt) {
bool yofsqffjff = false;
double jelrzcszlbgs = 42257;
int hmenbgxtltqiio = 3403;
string vghbnlane = "flocyxsyrjvekalwjdirutzgiyljhcyfbwvziygidwurdfvv";
double zauajwrpu = 8971;
double pbpsqcupkdjfdk = 11229;
bool wypzph = true;
int ospiuskaneprl = 1582;
bool ccnyto = false;
if (string("flocyxsyrjvekalwjdirutzgiyljhcyfbwvziygidwurdfvv") != string("flocyxsyrjvekalwjdirutzgiyljhcyfbwvziygidwurdfvv")) {
int nhrroj;
for (nhrroj=79; nhrroj > 0; nhrroj--) {
continue;
} 
}
if (42257 == 42257) {
int dclymelp;
for (dclymelp=68; dclymelp > 0; dclymelp--) {
continue;
} 
}
return string("agnrtcjfa");
}

int ppvmivi::uvlsfzjqldifczvpbbsugel(double lvafhmkomxdaq, string yhfozv, int totch, string vkvvahykuipiol, string udvli, int wgtratghntshnk, string gusiacyqtk, int nyscxrnojx, int icimkigak, int hldrliwpepx) {
string xppwqcdrc = "uvzumkojlivlxmfdnnhwjdohxmuyxflvugnmrgvfxvpvzkcaerchqbxntqtchaohtsnxnstaweyeauibmdotip";
double jsxopyafcbrxb = 11812;
double sqmuwlnwstbsnop = 92311;
bool grudhdpgyopc = true;
bool pxpaddk = true;
bool irwghuwjkgr = false;
bool zslngxyxg = true;
int aftdth = 2787;
double onzvlytyoxgfjx = 78249;
double bljplxftnico = 86465;
if (86465 == 86465) {
int lmrpubuq;
for (lmrpubuq=98; lmrpubuq > 0; lmrpubuq--) {
continue;
} 
}
if (86465 != 86465) {
int zewk;
for (zewk=41; zewk > 0; zewk--) {
continue;
} 
}
return 11156;
}

string ppvmivi::itketefceavleqqizqtcffn(int ktsslcaysqak) {
double zvevg = 42250;
double gwtqtzfmx = 5272;
int angszbntgd = 616;
if (5272 != 5272) {
int ctuudude;
for (ctuudude=40; ctuudude > 0; ctuudude--) {
continue;
} 
}
if (5272 == 5272) {
int iwi;
for (iwi=89; iwi > 0; iwi--) {
continue;
} 
}
if (42250 == 42250) {
int zk;
for (zk=33; zk > 0; zk--) {
continue;
} 
}
return string("");
}

void ppvmivi::qdfskvqpponyzgwoufggp(bool zbprwwxqlsnf, double njrlkr) {
bool rtegevodtkzgxj = false;
double dfrsplgihmzoigu = 52952;
bool abdfmoj = false;
int ygcnsvxoplz = 318;
bool exyvcwkayqloan = false;
double zvoellwhpukhar = 80261;
bool ffcdkrtacbtgp = true;
int ofalooghvhuktj = 98;
string hcwkq = "xuclonnrjfcaujpdivyfroudgfy";
if (false != false) {
int iixm;
for (iixm=2; iixm > 0; iixm--) {
continue;
} 
}

}

void ppvmivi::idglokpobsavwozdzpanwqf(bool kaarkmzi) {

}

int ppvmivi::uyaudqetqgkwgrkjtt(string nptyeqtejks, bool guacvgxjfs, bool zxkzj, bool vvwnrtu, string qrjjcwakskxgatm, double gtcccyhryyzlqbm, bool vlcztox, bool cibduczz, double nsddw) {
string bzactklexam = "jrwxourmnfjtzafbtiuqfqegwbiwjfuviwrtmy";
double rfifmkoeehqv = 914;
bool tekqvqmnyuvfvf = true;
string eptkhud = "odcrytmbctuowfkzmgmhhjxdxhnmzageuelbmjiksfwpywyt";
double gjzxnarqkunvgc = 36841;
if (914 == 914) {
int jgemxita;
for (jgemxita=9; jgemxita > 0; jgemxita--) {
continue;
} 
}
if (string("odcrytmbctuowfkzmgmhhjxdxhnmzageuelbmjiksfwpywyt") == string("odcrytmbctuowfkzmgmhhjxdxhnmzageuelbmjiksfwpywyt")) {
int rpozqp;
for (rpozqp=39; rpozqp > 0; rpozqp--) {
continue;
} 
}
if (string("jrwxourmnfjtzafbtiuqfqegwbiwjfuviwrtmy") != string("jrwxourmnfjtzafbtiuqfqegwbiwjfuviwrtmy")) {
int qfeevdlrnk;
for (qfeevdlrnk=52; qfeevdlrnk > 0; qfeevdlrnk--) {
continue;
} 
}
if (string("jrwxourmnfjtzafbtiuqfqegwbiwjfuviwrtmy") != string("jrwxourmnfjtzafbtiuqfqegwbiwjfuviwrtmy")) {
int vvelpaja;
for (vvelpaja=25; vvelpaja > 0; vvelpaja--) {
continue;
} 
}
return 19554;
}

int ppvmivi::tpilktqebrslvpvqufifrx(double ccttitcxnfm, double vssudizpee, bool akxxaqrj, bool thakhmalnnv, bool ctdivasxwdu, string inrxgbldwd, double fegziqs, double vipklpmxqau, bool vsdecir, int zuttxjqcn) {
return 22989;
}

double ppvmivi::vdozajfztcemh(bool xnnhxkmuebnuqw, string ygeibvvrxxp) {
double rbjdelp = 27673;
string mkppjdekntai = "yfjlpsipcrrzhvftcozttvtxavpowllmoqhjmazdekwzzxcq";
bool tbcvt = true;
int keunchg = 1799;
string oipwdajmtnnlxv = "zvyjjvymvxjmuxusryaqrjcbujgruzushdhzhyjkmuhdfybuwrvuwvtusoqpwrtb";
bool zjtvnizmc = true;
string dvmvutrikisdqal = "qrgmhvkudyotsyatmpxfmyznrmwmtznhpshfqiylcndpiglndeizsiabupxvttt";
return 55233;
}

void ppvmivi::ojwjabcimu(bool yxlyvzxzfwe, double otygt, string stujczmsoo, int stjkxedrw, string nwsdycuw) {
string gchrcjavyohayw = "lbhgvftfnhimadaclcqxfjlwsonygyzwfpjnlprpwcwofjppxwctbnczfeztpqjnicdqqyrvvj";
int wzoosdo = 2410;
if (2410 != 2410) {
int tumvqioy;
for (tumvqioy=68; tumvqioy > 0; tumvqioy--) {
continue;
} 
}
if (string("lbhgvftfnhimadaclcqxfjlwsonygyzwfpjnlprpwcwofjppxwctbnczfeztpqjnicdqqyrvvj") == string("lbhgvftfnhimadaclcqxfjlwsonygyzwfpjnlprpwcwofjppxwctbnczfeztpqjnicdqqyrvvj")) {
int umytdaqz;
for (umytdaqz=12; umytdaqz > 0; umytdaqz--) {
continue;
} 
}
if (string("lbhgvftfnhimadaclcqxfjlwsonygyzwfpjnlprpwcwofjppxwctbnczfeztpqjnicdqqyrvvj") != string("lbhgvftfnhimadaclcqxfjlwsonygyzwfpjnlprpwcwofjppxwctbnczfeztpqjnicdqqyrvvj")) {
int qfi;
for (qfi=20; qfi > 0; qfi--) {
continue;
} 
}
if (string("lbhgvftfnhimadaclcqxfjlwsonygyzwfpjnlprpwcwofjppxwctbnczfeztpqjnicdqqyrvvj") != string("lbhgvftfnhimadaclcqxfjlwsonygyzwfpjnlprpwcwofjppxwctbnczfeztpqjnicdqqyrvvj")) {
int pk;
for (pk=44; pk > 0; pk--) {
continue;
} 
}

}

double ppvmivi::rshedmxcirivvu(int hiqyublh, double kxceojgnzxw, string fcurcwbgm, string oilrivl, string nltbgvrwawxn) {
string zgbvuwqowvhs = "jighqcxxeszdvmlkwuuotocjtvqwpiovbgqqjvylukfarhrbyjgngychsqncdhntqecbdwxzoetqifvbeyscjoqtsinvxpbsr";
double ljsxdervad = 3746;
double ltmvk = 9561;
string ezfmzvxbsg = "fqzwlcwjznwngnlxrgqek";
double fwhktpighfvn = 11097;
if (11097 != 11097) {
int mzr;
for (mzr=62; mzr > 0; mzr--) {
continue;
} 
}
if (9561 == 9561) {
int bxcalze;
for (bxcalze=2; bxcalze > 0; bxcalze--) {
continue;
} 
}
if (string("fqzwlcwjznwngnlxrgqek") == string("fqzwlcwjznwngnlxrgqek")) {
int isewxfjgf;
for (isewxfjgf=47; isewxfjgf > 0; isewxfjgf--) {
continue;
} 
}
if (string("fqzwlcwjznwngnlxrgqek") != string("fqzwlcwjznwngnlxrgqek")) {
int rceiemsby;
for (rceiemsby=9; rceiemsby > 0; rceiemsby--) {
continue;
} 
}
if (string("fqzwlcwjznwngnlxrgqek") == string("fqzwlcwjznwngnlxrgqek")) {
int xhqvz;
for (xhqvz=44; xhqvz > 0; xhqvz--) {
continue;
} 
}
return 45458;
}

ppvmivi::ppvmivi() {
this->rshedmxcirivvu(1329, 10137, string("cgrgl"), string("nxtnqbbsrbaofbgyadvwvypfjcpfuwbtqwprdbjyemfvpghwsztfsxyigczhstukrlewj"), string("ukpsorezhwyzxgdeh"));
this->uvlsfzjqldifczvpbbsugel(25334, string("eqkuqxtcmqaxaqyegzyupdxfauzmxhafzmiiadimetmanhtyuwftsypqxmvjhxmnl"), 649, string("aacwibgpojkodpkenhbkoblmdjqmawscbfbcoldiaclrpuamfrchnlxezxqktowllmifufbiiepitwebtvuocrwncowlihrry"), string("ydqcduwulgsfglgczfaqcozjyb"), 351, string("chvfeodacyfzjdlvsntsjdmtxehpyogzvqcgvkjorhnviavpqmulejgslqyzf"), 2138, 8, 318);
this->itketefceavleqqizqtcffn(1466);
this->qdfskvqpponyzgwoufggp(true, 15735);
this->idglokpobsavwozdzpanwqf(true);
this->uyaudqetqgkwgrkjtt(string("fsszotltqpercxpzlwneepfiipoxdxgeypcv"), false, true, false, string("ldkxxbriwjxkrjvkctkfwfnytyujccsmjdangziypkcrqskxmbwxprealrktsxqsaouwmi"), 14934, true, true, 14349);
this->tpilktqebrslvpvqufifrx(26472, 12909, true, false, false, string("kvzkrhqltohktknyyazlapzejvvevyjgwxsgwsckgksbsrnpimvnvldpzszpyedtfnbeewdhpkrnuwczrfkxicwqcxhhqthbs"), 6208, 16400, true, 4537);
this->vdozajfztcemh(true, string("lcsnnxwbgqhzdfsfiwqdhlolairerqotjtyxpwowajcjvdgixtz"));
this->ojwjabcimu(false, 24760, string("ejcuadyqyreooxxsewwtfqntkbhpspxtzwwbbvjeejnskljkmdyqpyyuxdnkctlzyjdkfahpmpopjuvkfzwdhj"), 3001, string("sgjwqqgtlsdmbijsyouxkcnaficmqjocfwfxillyrrppsgiyj"));
this->zuknkhqrhkxuljktpckpbpd(true, 5546, 1420, 1554, 12852, 6919);
this->ablafauotvmckhessvp(string("femnpjolrfctoifqoajyqtuttvhjfcwgsllxnhcovmilon"), 5890, string("jvycupwkivstyhdbkgdlmnuclcoynrmvkclnxffciwseqfvuemxdzylrdfcnqsopyumjhdtsofziryswpxahaljtxa"), false, false);
this->uigkrfrkwhxtrejfwlcsc(9606, true, string("pylnvknethxmfgj"), true, string("hvuczvyfiidshkislrktztwkgrzdnozyzcxpxgg"), true, string("lhprtxgnusfmaxvbpmhlzabxnjzzlkyqoqhpxrtmgzyw"), 14799, 17647, 21096);
this->pgavwibftwzkt(1522, 40618, 3622, 7511, true, 20894, 456, string("vwvlovapsyeotihcvmorswoobwttspsyppssnwvwhodnyxfhda"), 5559);
this->ocjgqdrthtyuubigfajbw(22148, 5234, false, false, 6031, 754, string("qwbvmanmkeenrwjsakebfxcwaouimptulqxireaqcxaobkkoluxyffgrcvpdittmbnfyygussgnotedecgseoorimvgwtrwzwzop"), false, 303, 4273);
this->qreikhlnlpjs(2442, 3359, 810, 2869, 250, 25621);
this->qvkzrzetybmohqfpt(7460, 1029);
this->cjfnimpdcgi(string("cefeasljklysnmyouacmbn"), true, string("yjjjggcftoeh"), 28334);
this->pvkjzbnhimhthtxdc(string("lfpqwgwbqevcbitdyhakxcreo"), false, 33768, 2925);
this->mqbovmjfoeixmqnvr(string("cjzgordvsobrgqhkrordaahpnlotmjz"), 21265, 566, 2942, string("esjjoamawyiqjtdocunsiqkgbftkluwvkyylxdjarmcjbsadvppcqlcapqdomnziaioqxqlzmyaeaxofmmtxw"));
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class xxyjljk {
public:
bool zzbbgamd;
int ylzpi;
int hrrypdfowv;
double ihkfgypwszj;
xxyjljk();
double diakfregzrmemnlwik(int vjfgcwgmuwzqglk, bool rtkdmbowfps, bool tarmjrhby, double deuozojtbxalm, string zbywd, string bjytt, bool pluueu, string ceskek);
string jriqqoohcbsb(string mokqatue, bool rpdlimz, bool doafrlo, string wfvpexmoiu, double doukndktvfog, double uieljsfaagfsktb, int ixyknxynlviqbkj, double zqfptubqd, double jnonpjkrio);
void oinfpvqyznnvpfnwilzbyjmx(double mnzbccjjl, int msxfjcbhhii, int holvia, bool ixvpbqqiz, double yzdwxn, bool fpwhphalicy, string vwjvquwaf, int lcpikllxh);
string hhxoxtxfltov(string xlrlyvbfimhugsj, string gztbwnqduxurknd, bool opqsmffcbc, double bhvlgd, bool mrmrtguk, int csmcwtctt, string ecjwzz, bool bhrtmyobwxzzov);
void lzhrlaokwnmihganbjwz(double cehdxrdgd, double wzczekn, int mrqxrz, string xqymx, int scmdf, double ecvpzas, bool jnfsarodbf, int qylux, bool xpsnkwpwtl);
double sqrevteite(int zbbcuruhspzjw, int pyempnwsjbvkydy, bool mavcqyhoskfccdb, bool hpqwhpzzknpvb, bool fmozi, bool ibemvb, double rzdzzco, double xfxltfobgkkgib);
void aibeqgvasnvxtdcmf(double umiyiabfjwn, string wclnzsxydiiyx, double rrnpogekt, bool wwgeoxifty, string okyhnpgrkidl, double jmolhhvbczvzdg, int pcydnnytpztbk, double ynghdyrkuwoqzm, string sbwef, string ujmeejze);
void rlfrmeadasld(int uvudu, bool yxfsfpmt, bool qvpckifp);

protected:
string klgnbklttfjhlt;
bool mzhwkohqm;

string nwoerjgoxfgolqjd(string kjjxybf, bool ksfyffcpwb, int fhxrc, bool fvlsrlztte, int bwyzrvwbfpbwnwy, bool hzkzidaiaejujqb, double fepuiafqvcn, bool gdsinrpquopl, bool rmadrjiarndn, bool fuwpkiw);
void iwpwnqdtkyvycfwbe(double tzcbn, double oanyse, int vdfhczcwnptgy, bool uuvtuuwqub, int dytaidbxmpgisgd, double gocvxt);
int ajkivuszlv(double hoqjmh);
int lncyvyesxqgbhdcejoowju();
int sofpdhlttyvjferywjcjfjd(string cvgbxsskufy, int trnwnnnrz, bool nxjakzgqx);
int jrugxnrvee(string nbdmtdcpbn, double gstmizuowowjldq, string jiszbkuul, bool xccyndafuaq, bool qtaqkgvhbdetfvz, bool zgeixmlenae, bool ybmtcv, int aynauaiqmqucriv, string nigwtp, string aktbnumwauexbvb);
double zwhribastsjo(int kkiwumqo);
bool zbubjqryrblkdoaozfxbs(int evqmezg, int mvzrlebrdlcvc);

private:
double lborlinakrlrka;
bool lgawqsouuqtasw;
double kybcfmjldzn;
int gpgfobbmts;

string iefrmkwscvcurmo(double iygriblpdswjbjj, bool vwzzkvcvekl, string vgyufqarjygc, int oduaufdrxhkmekr, int kzvqyru, bool cbifjhslaq, bool awswcsgtxxdoy, string bqsdxlnyaoaunp, int tcfoa);
int vucubtocqtlrwq(int oqiqkmrr, int xhjbemwukiti);
bool qjdiaswpqstob(bool ozmkuhcfol);

};




string xxyjljk::iefrmkwscvcurmo(double iygriblpdswjbjj, bool vwzzkvcvekl, string vgyufqarjygc, int oduaufdrxhkmekr, int kzvqyru, bool cbifjhslaq, bool awswcsgtxxdoy, string bqsdxlnyaoaunp, int tcfoa) {
double zmnshdoaagmg = 78860;
if (78860 != 78860) {
int wy;
for (wy=17; wy > 0; wy--) {
continue;
} 
}
if (78860 == 78860) {
int bjomfae;
for (bjomfae=4; bjomfae > 0; bjomfae--) {
continue;
} 
}
if (78860 == 78860) {
int ruzklxpsn;
for (ruzklxpsn=25; ruzklxpsn > 0; ruzklxpsn--) {
continue;
} 
}
return string("ylkrdyslo");
}

int xxyjljk::vucubtocqtlrwq(int oqiqkmrr, int xhjbemwukiti) {
int fojbserwgukjlpu = 3530;
string qyegjhvrw = "mjqpckakytrcpkvbobqfofrismwgsawmbkmzgautfkpmipgoimfh";
string iaxipioaipqydny = "nlarbiaqnyliaxod";
int qjbvszyumowqq = 2544;
double czkrgdhmlri = 15332;
if (2544 == 2544) {
int axqoung;
for (axqoung=28; axqoung > 0; axqoung--) {
continue;
} 
}
if (2544 == 2544) {
int qqph;
for (qqph=10; qqph > 0; qqph--) {
continue;
} 
}
if (3530 == 3530) {
int rpmdwlyzqp;
for (rpmdwlyzqp=69; rpmdwlyzqp > 0; rpmdwlyzqp--) {
continue;
} 
}
if (15332 != 15332) {
int zwnlkwh;
for (zwnlkwh=39; zwnlkwh > 0; zwnlkwh--) {
continue;
} 
}
return 44112;
}

bool xxyjljk::qjdiaswpqstob(bool ozmkuhcfol) {
double apnmk = 48402;
bool bfpwedjxieesh = true;
double okraslwvx = 65081;
bool teesrwftlptuvps = false;
bool xyhgdg = false;
bool psnqub = false;
int pjnzrwcuoeu = 2493;
if (2493 == 2493) {
int wzammusa;
for (wzammusa=25; wzammusa > 0; wzammusa--) {
continue;
} 
}
if (false == false) {
int djnlbf;
for (djnlbf=55; djnlbf > 0; djnlbf--) {
continue;
} 
}
if (65081 != 65081) {
int qvrfzf;
for (qvrfzf=25; qvrfzf > 0; qvrfzf--) {
continue;
} 
}
if (2493 != 2493) {
int qszq;
for (qszq=96; qszq > 0; qszq--) {
continue;
} 
}
if (2493 != 2493) {
int nfp;
for (nfp=21; nfp > 0; nfp--) {
continue;
} 
}
return true;
}

string xxyjljk::nwoerjgoxfgolqjd(string kjjxybf, bool ksfyffcpwb, int fhxrc, bool fvlsrlztte, int bwyzrvwbfpbwnwy, bool hzkzidaiaejujqb, double fepuiafqvcn, bool gdsinrpquopl, bool rmadrjiarndn, bool fuwpkiw) {
return string("ljqoxyfkwh");
}

void xxyjljk::iwpwnqdtkyvycfwbe(double tzcbn, double oanyse, int vdfhczcwnptgy, bool uuvtuuwqub, int dytaidbxmpgisgd, double gocvxt) {
double prpcgdb = 18999;
double crkhp = 22908;
string emkwftc = "cqiazjayi";
if (string("cqiazjayi") != string("cqiazjayi")) {
int fywtvk;
for (fywtvk=60; fywtvk > 0; fywtvk--) {
continue;
} 
}
if (string("cqiazjayi") != string("cqiazjayi")) {
int zlsctljhbf;
for (zlsctljhbf=84; zlsctljhbf > 0; zlsctljhbf--) {
continue;
} 
}
if (22908 == 22908) {
int kuexbytvx;
for (kuexbytvx=11; kuexbytvx > 0; kuexbytvx--) {
continue;
} 
}

}

int xxyjljk::ajkivuszlv(double hoqjmh) {
bool sqlxgdfpl = true;
bool dwlxb = true;
bool nlclcpuqzfna = true;
int iluqhnunvwo = 581;
double keucitia = 21634;
int yitybu = 656;
bool nbsosrazvl = true;
int bakkdklpggizfx = 1104;
if (true == true) {
int ntssp;
for (ntssp=5; ntssp > 0; ntssp--) {
continue;
} 
}
if (581 == 581) {
int lhwndwwn;
for (lhwndwwn=92; lhwndwwn > 0; lhwndwwn--) {
continue;
} 
}
if (true == true) {
int rilxqx;
for (rilxqx=77; rilxqx > 0; rilxqx--) {
continue;
} 
}
if (1104 != 1104) {
int ko;
for (ko=67; ko > 0; ko--) {
continue;
} 
}
return 97710;
}

int xxyjljk::lncyvyesxqgbhdcejoowju() {
double bsjogkxa = 30954;
int iehjtxnxo = 449;
bool jslkilq = true;
bool vbram = false;
string faezfrcsr = "quthpritputixvzvownycyncab";
double liggdmgpwf = 16633;
if (30954 != 30954) {
int tdrasnkouj;
for (tdrasnkouj=67; tdrasnkouj > 0; tdrasnkouj--) {
continue;
} 
}
return 43447;
}

int xxyjljk::sofpdhlttyvjferywjcjfjd(string cvgbxsskufy, int trnwnnnrz, bool nxjakzgqx) {
string qrrjprgwaoaghwe = "otgogrfavvkkzjtzzcwemnizlwghcafpohovjiddlhtynjnfxdwegnq";
string ipiiz = "mcxrhojbgaarlaikwedazdvknqgpmqsiygcehnbmayghdttoniaqistvedivzqajo";
string vijzmp = "fbqngqxpmrxawrlvyodqbkhjwhvcapzbsxjumypogssmirmpleccqkhdwholbyzyddngafvbcpwrpze";
int kykltnlydfgau = 4764;
string pzkzlehhu = "gvjhjaxzuhbpbovuqcpholoumxalgqpxausmi";
int ynyocyvzgjxbt = 1580;
int dbdsril = 4988;
bool iupfg = true;
bool olijmovpdnip = false;
if (string("fbqngqxpmrxawrlvyodqbkhjwhvcapzbsxjumypogssmirmpleccqkhdwholbyzyddngafvbcpwrpze") == string("fbqngqxpmrxawrlvyodqbkhjwhvcapzbsxjumypogssmirmpleccqkhdwholbyzyddngafvbcpwrpze")) {
int qpvzpfoo;
for (qpvzpfoo=49; qpvzpfoo > 0; qpvzpfoo--) {
continue;
} 
}
if (false != false) {
int iqmvvzcxgk;
for (iqmvvzcxgk=88; iqmvvzcxgk > 0; iqmvvzcxgk--) {
continue;
} 
}
if (string("mcxrhojbgaarlaikwedazdvknqgpmqsiygcehnbmayghdttoniaqistvedivzqajo") == string("mcxrhojbgaarlaikwedazdvknqgpmqsiygcehnbmayghdttoniaqistvedivzqajo")) {
int lsamlxifdp;
for (lsamlxifdp=54; lsamlxifdp > 0; lsamlxifdp--) {
continue;
} 
}
if (string("mcxrhojbgaarlaikwedazdvknqgpmqsiygcehnbmayghdttoniaqistvedivzqajo") != string("mcxrhojbgaarlaikwedazdvknqgpmqsiygcehnbmayghdttoniaqistvedivzqajo")) {
int bjqauv;
for (bjqauv=45; bjqauv > 0; bjqauv--) {
continue;
} 
}
if (string("otgogrfavvkkzjtzzcwemnizlwghcafpohovjiddlhtynjnfxdwegnq") == string("otgogrfavvkkzjtzzcwemnizlwghcafpohovjiddlhtynjnfxdwegnq")) {
int klniv;
for (klniv=79; klniv > 0; klniv--) {
continue;
} 
}
return 58487;
}

int xxyjljk::jrugxnrvee(string nbdmtdcpbn, double gstmizuowowjldq, string jiszbkuul, bool xccyndafuaq, bool qtaqkgvhbdetfvz, bool zgeixmlenae, bool ybmtcv, int aynauaiqmqucriv, string nigwtp, string aktbnumwauexbvb) {
return 58089;
}

double xxyjljk::zwhribastsjo(int kkiwumqo) {
int tendslpkn = 4331;
bool iduwm = true;
bool cflfalgphtbsij = false;
bool hbqml = true;
if (false != false) {
int jmnxefqjjx;
for (jmnxefqjjx=82; jmnxefqjjx > 0; jmnxefqjjx--) {
continue;
} 
}
return 76712;
}

bool xxyjljk::zbubjqryrblkdoaozfxbs(int evqmezg, int mvzrlebrdlcvc) {
string xfwqrgvpilqznvn = "efmfscficdnvzqlwocjusxlncftyigipmejmnwn";
string qfzxylfmorsobas = "etktuiauujpvm";
bool ginqqpkqv = true;
bool vajzogkeind = false;
bool tbkcydvvajsuvw = true;
string cimhjrsvtnl = "onyoznvpnlziaospmgakzucdtrvfobeiwxuukxdnvdtlntcqistvgyqylndytwrdamomusgahxz";
int dwyqkrkogytzmi = 1079;
string ebisgvqxuuxeeg = "jboxinvcqzsigxnenwbyocwhmvfvibqzxqxpixktwcaigdokzkdbnpieblpntjglltfjgkjehycovbbzjyhtyzkoztfgwy";
if (true == true) {
int dyvqyszlw;
for (dyvqyszlw=3; dyvqyszlw > 0; dyvqyszlw--) {
continue;
} 
}
if (string("onyoznvpnlziaospmgakzucdtrvfobeiwxuukxdnvdtlntcqistvgyqylndytwrdamomusgahxz") == string("onyoznvpnlziaospmgakzucdtrvfobeiwxuukxdnvdtlntcqistvgyqylndytwrdamomusgahxz")) {
int jqi;
for (jqi=78; jqi > 0; jqi--) {
continue;
} 
}
if (false != false) {
int im;
for (im=33; im > 0; im--) {
continue;
} 
}
if (string("efmfscficdnvzqlwocjusxlncftyigipmejmnwn") == string("efmfscficdnvzqlwocjusxlncftyigipmejmnwn")) {
int zocajcsii;
for (zocajcsii=34; zocajcsii > 0; zocajcsii--) {
continue;
} 
}
return false;
}

double xxyjljk::diakfregzrmemnlwik(int vjfgcwgmuwzqglk, bool rtkdmbowfps, bool tarmjrhby, double deuozojtbxalm, string zbywd, string bjytt, bool pluueu, string ceskek) {
return 86025;
}

string xxyjljk::jriqqoohcbsb(string mokqatue, bool rpdlimz, bool doafrlo, string wfvpexmoiu, double doukndktvfog, double uieljsfaagfsktb, int ixyknxynlviqbkj, double zqfptubqd, double jnonpjkrio) {
double bgngnrlunryb = 34279;
string xwwmsqv = "kvoyxdefgoqwmnxlyzujppiowwuuxvryjxkcgzkvrniusalgfobqocswvvaepbhbbrrhkipwinjakuqyqrzunsi";
string nbclfhpyux = "fauvpfozcjgkickepvriyzzmrkjiefjycsibovbgztkaoygrzxacadbntesqkqcnfopjuvkvesocpiztrjyclfeziqtbhp";
if (string("fauvpfozcjgkickepvriyzzmrkjiefjycsibovbgztkaoygrzxacadbntesqkqcnfopjuvkvesocpiztrjyclfeziqtbhp") != string("fauvpfozcjgkickepvriyzzmrkjiefjycsibovbgztkaoygrzxacadbntesqkqcnfopjuvkvesocpiztrjyclfeziqtbhp")) {
int rwym;
for (rwym=2; rwym > 0; rwym--) {
continue;
} 
}
if (string("fauvpfozcjgkickepvriyzzmrkjiefjycsibovbgztkaoygrzxacadbntesqkqcnfopjuvkvesocpiztrjyclfeziqtbhp") == string("fauvpfozcjgkickepvriyzzmrkjiefjycsibovbgztkaoygrzxacadbntesqkqcnfopjuvkvesocpiztrjyclfeziqtbhp")) {
int gybtezepk;
for (gybtezepk=55; gybtezepk > 0; gybtezepk--) {
continue;
} 
}
if (34279 == 34279) {
int nect;
for (nect=34; nect > 0; nect--) {
continue;
} 
}
if (string("kvoyxdefgoqwmnxlyzujppiowwuuxvryjxkcgzkvrniusalgfobqocswvvaepbhbbrrhkipwinjakuqyqrzunsi") == string("kvoyxdefgoqwmnxlyzujppiowwuuxvryjxkcgzkvrniusalgfobqocswvvaepbhbbrrhkipwinjakuqyqrzunsi")) {
int gwapcgh;
for (gwapcgh=66; gwapcgh > 0; gwapcgh--) {
continue;
} 
}
if (string("kvoyxdefgoqwmnxlyzujppiowwuuxvryjxkcgzkvrniusalgfobqocswvvaepbhbbrrhkipwinjakuqyqrzunsi") == string("kvoyxdefgoqwmnxlyzujppiowwuuxvryjxkcgzkvrniusalgfobqocswvvaepbhbbrrhkipwinjakuqyqrzunsi")) {
int zeptbpfqo;
for (zeptbpfqo=97; zeptbpfqo > 0; zeptbpfqo--) {
continue;
} 
}
return string("shfwwifl");
}

void xxyjljk::oinfpvqyznnvpfnwilzbyjmx(double mnzbccjjl, int msxfjcbhhii, int holvia, bool ixvpbqqiz, double yzdwxn, bool fpwhphalicy, string vwjvquwaf, int lcpikllxh) {
double lbwqghxkh = 6599;
bool nsjyejvztoj = false;

}

string xxyjljk::hhxoxtxfltov(string xlrlyvbfimhugsj, string gztbwnqduxurknd, bool opqsmffcbc, double bhvlgd, bool mrmrtguk, int csmcwtctt, string ecjwzz, bool bhrtmyobwxzzov) {
int ttarbg = 131;
double fbzlvbwuxj = 4421;
string elvjvzjrpve = "eapzysohkjesjamsuiiopawglweavwvowyfamsfvxavkqqpuoepdzomzvllvujrhfbygstmkjzdapozembczscaoka";
if (131 != 131) {
int bhyclv;
for (bhyclv=66; bhyclv > 0; bhyclv--) {
continue;
} 
}
if (131 == 131) {
int awhvxnnfw;
for (awhvxnnfw=73; awhvxnnfw > 0; awhvxnnfw--) {
continue;
} 
}
if (string("eapzysohkjesjamsuiiopawglweavwvowyfamsfvxavkqqpuoepdzomzvllvujrhfbygstmkjzdapozembczscaoka") != string("eapzysohkjesjamsuiiopawglweavwvowyfamsfvxavkqqpuoepdzomzvllvujrhfbygstmkjzdapozembczscaoka")) {
int yoeggr;
for (yoeggr=86; yoeggr > 0; yoeggr--) {
continue;
} 
}
if (4421 == 4421) {
int kneeaqp;
for (kneeaqp=41; kneeaqp > 0; kneeaqp--) {
continue;
} 
}
return string("fghuejosonqhaj");
}

void xxyjljk::lzhrlaokwnmihganbjwz(double cehdxrdgd, double wzczekn, int mrqxrz, string xqymx, int scmdf, double ecvpzas, bool jnfsarodbf, int qylux, bool xpsnkwpwtl) {
bool tbexak = false;
int kmxtdgs = 1611;
bool dvpnqajy = true;
bool nkkqtzlmde = true;
if (true != true) {
int xikmfuyx;
for (xikmfuyx=53; xikmfuyx > 0; xikmfuyx--) {
continue;
} 
}
if (true != true) {
int gtnanv;
for (gtnanv=51; gtnanv > 0; gtnanv--) {
continue;
} 
}
if (true == true) {
int kktkkx;
for (kktkkx=10; kktkkx > 0; kktkkx--) {
continue;
} 
}
if (1611 != 1611) {
int zwmvsmnrp;
for (zwmvsmnrp=73; zwmvsmnrp > 0; zwmvsmnrp--) {
continue;
} 
}

}

double xxyjljk::sqrevteite(int zbbcuruhspzjw, int pyempnwsjbvkydy, bool mavcqyhoskfccdb, bool hpqwhpzzknpvb, bool fmozi, bool ibemvb, double rzdzzco, double xfxltfobgkkgib) {
double wiokob = 3512;
string blwyhcw = "eic";
string tkwydg = "avstpiwefjugsgblvgovajyyfeioaucaedwnyhxkddaotrhjbyxsquyfdvxximgoawxfgyhvudluvnsjclhujh";
int avznuesyxc = 1091;
double kzctlzruoknsi = 4500;
string uvglrmilggpk = "lzpsswssthenorwpkmbbngpctgtvahtcypqdtjmhvmmmflnmptbgjkgcftssurlizvumhkapgrsadxliykexuckpyqy";
if (string("lzpsswssthenorwpkmbbngpctgtvahtcypqdtjmhvmmmflnmptbgjkgcftssurlizvumhkapgrsadxliykexuckpyqy") != string("lzpsswssthenorwpkmbbngpctgtvahtcypqdtjmhvmmmflnmptbgjkgcftssurlizvumhkapgrsadxliykexuckpyqy")) {
int iazh;
for (iazh=44; iazh > 0; iazh--) {
continue;
} 
}
if (3512 != 3512) {
int blfdxpmtn;
for (blfdxpmtn=12; blfdxpmtn > 0; blfdxpmtn--) {
continue;
} 
}
return 67037;
}

void xxyjljk::aibeqgvasnvxtdcmf(double umiyiabfjwn, string wclnzsxydiiyx, double rrnpogekt, bool wwgeoxifty, string okyhnpgrkidl, double jmolhhvbczvzdg, int pcydnnytpztbk, double ynghdyrkuwoqzm, string sbwef, string ujmeejze) {
bool gcijxsrplpzyzav = true;
string efatgxwevwfmpze = "lcvgkmkumdx";
int zebqqovlokcohb = 528;
string pcwjeuji = "grc";
bool vkwseqqv = false;
double lsjikdl = 12605;
string dohvlkjr = "dgdcqansisv";
double ohgjmcnbw = 13761;
if (false != false) {
int eydgvyj;
for (eydgvyj=99; eydgvyj > 0; eydgvyj--) {
continue;
} 
}
if (true != true) {
int vwfnhitzot;
for (vwfnhitzot=60; vwfnhitzot > 0; vwfnhitzot--) {
continue;
} 
}
if (string("grc") == string("grc")) {
int khpegmkfp;
for (khpegmkfp=70; khpegmkfp > 0; khpegmkfp--) {
continue;
} 
}

}

void xxyjljk::rlfrmeadasld(int uvudu, bool yxfsfpmt, bool qvpckifp) {

}

xxyjljk::xxyjljk() {
this->diakfregzrmemnlwik(4305, false, true, 9668, string("ykvdkkbqzddhtwedwncohtyzyhsgowgrauawbeuirsveoyyuzwqxikxnitpvdyljbxuwbimmlrxrqbwxvairiohwxeuzf"), string("niqxexgdhdvbcqtl"), true, string("hfukhvewdkzkyipsorcxdxnydgznmkbqgeelxlbwzgbwqwfkwrpdtvnfrk"));
this->jriqqoohcbsb(string("bdmrwssgawtgapbvdxwqwxdzsolurphlbsnqkupqfohwgtlluybqwevzerxvawfhbmmtvzxhwyjngessdwyfxckft"), true, true, string("ezjhdguvopuoohcmadbfpwcacyudqqrvgmhertgeqrbkuktxjwaxthzmyfrskvundwqznnuujwmxbeokhdhavhyqhwhkch"), 43836, 26439, 3416, 17097, 593);
this->oinfpvqyznnvpfnwilzbyjmx(40125, 2244, 4721, true, 63785, false, string("ewztvhyrfrxcsxsuxqvvvnwdycoltlgkvdixrcgkyujgoukzgcrpxy"), 1903);
this->hhxoxtxfltov(string("dorgzpklalgeogiggnhqcprgefuccgqtlbbpghmmlptpysocztayevivhabudsinwwadygcj"), string("rxbbxjjfvogevjspeuxjmuscdkjfxvbgxwlud"), false, 18916, true, 1277, string("qqottmzhzihzhzqtrmojyx"), false);
this->lzhrlaokwnmihganbjwz(40537, 3312, 4506, string("yvzeruldkqulqkixcngveealsxnpqc"), 2031, 773, false, 260, true);
this->sqrevteite(2132, 3469, true, false, true, false, 46388, 2670);
this->aibeqgvasnvxtdcmf(45324, string("nrznjigfghzhqnxfpvsaknhzotocvutotetxdo"), 49951, false, string("cytcchzfzabzihrkxxuixldpnlgokfbkarrqyfszntrjkmzgqi"), 27422, 1108, 19055, string("bgqmlddlsudxwoiagqoynscofbdpcvpmyeaylseijcssuwmzlwuavyzjlirixkwnegklzeudlimoaxs"), string("bexwbaotpdrukpfplhfojtbkmoaomehwtfdiedpvlmizfugckiuaguplcoknczfoetyooqitgmvzvcdowgwa"));
this->rlfrmeadasld(201, false, false);
this->nwoerjgoxfgolqjd(string("rciueovzdxkpaaswjemuvdwblkxipbamkbdherrbyhjywlkujepgjqflfwukkdrwnrazosevxqjtlhgzgjhvnsgxywvfwmptuga"), true, 5660, true, 1722, false, 12102, false, true, false);
this->iwpwnqdtkyvycfwbe(26015, 3976, 1253, false, 6108, 4364);
this->ajkivuszlv(8686);
this->lncyvyesxqgbhdcejoowju();
this->sofpdhlttyvjferywjcjfjd(string("wtlzz"), 1559, true);
this->jrugxnrvee(string("jyegwmamlqwpm"), 9905, string("silrfr"), true, false, true, false, 1770, string("fzqcbjymuazfolinsjqjmhbqpsjzvtkldkbborufouesbmewodvqgxgsyfuuchnewivhhiuquwvvzkqmemjcxh"), string(""));
this->zwhribastsjo(1642);
this->zbubjqryrblkdoaozfxbs(196, 44);
this->iefrmkwscvcurmo(32848, true, string("ejrtwgvlzoczxjgknlybcoiwrtlamyhdqmko"), 535, 1517, true, true, string("rcbwacsonsnhetovwmunckztwpycbemo"), 1283);
this->vucubtocqtlrwq(3634, 1080);
this->qjdiaswpqstob(false);
}


#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ikguplc {
public:
string rphflqywga;
ikguplc();
int skpuuswtjxopbqaqkrex(double pvcbuagdyqpbcf, bool ixsdmvzmoz, double jrwehybdkbei, bool rrhfz, double mqeqqytmdyfkgp, string jfshfhpsf, bool vwuqvvhgimvny, double ioaqeyd);
string bjlqdnatcfwgdx(double vvywsss, string dgkkkwxkytyxu, int ggqzwsooepqda);
bool aobjrfugyoydeitttefxyckgl(double gmjxuygurqzvb, string uskvslqu, int xivhpsx);
string mgwbyaopvttkmvobyia(double knpsd, string dgxvd, int zbnzqvgepnmks, bool lgfvnlzc);
void wzcdyvnvpv(int fljgafwlhpqdfy, string kaxijfazgys, string bcvlurzkwtfyir, string sddbzj, double bgxcafo, int pcolwiktrc, int dhjnhnizjiqfqbj);
void mcsscomelhdmbjzpzoeili(bool wusedfuocd, string wotbwzjlli, double zrmmaowodr, double vzaeueijxiicekc, int qngtiuck);
string bnjdvpwqcnudklxkbbkufznt(bool mllzil, int dxdsqrhlmlxsnd, bool srhcmwuaqdjuq, int avuywspx, bool gierxdwnhkpd);
string ylazttfqpma(string lewgpfwzdwaz);
string byzjfdfzxkhijetzahh();
string skbthnduozfjgxhrlyog(bool fdoidcx, int buhbmwqnab, double vatbgceu, int bsxzqvkzuz, string bidusnukwp, bool epyvgwujbyvbuwh);

protected:
string sgxismbzjaybgdy;
int lvyjcnxrsruzzuc;

double vmlmzlthwuugcbodea(double ovhxner, int pyaslcpcldkkmal, string ijtwrigoeqcgem, bool thsvvewn, string wsypdxrdyvnlc, double qbixhhewbz, string swpusjpw, bool tuxurjypuqzq, bool hptgvqwrazpcogq);
double gjaopguexotrt();
int aexdmbbudekone(double plnvtniffiier);
double eoloyyxwsarknssvvj(double stejzzylggxdzw, string morvjgvujfi, bool jkxsop, double zyxadi, double xuzoh, int ofvojldnn, double ddgpynhszbokp);
string qvioawukqie(int kwkicmognhq, bool mmnmvajuci, double vzxhdxx, bool sphybif, string kouhpwlx, bool afuvmnhqaxkl, string zcjkme, double gzbbxdnnmxovqy, double clwdpshxjteass, double pfcpdtykxb);
bool ixkmkigtahcthgbupprjtdtwt(string qdhfmgrp, int berpvtgv, double susejlzcbokywy, string pnvepk);
string vzjpnjltdpypf(bool gkohyk, string izaqiywgplcsjiw, double ptajkruj, bool hhmcuutkjginc);
string pulzwipmvrkpdexsie(double qrjomyeni, bool wxemfesvkv, int mfnsirbefkuds, string dgajtce, bool sfsyiokcba, int mwgzo, int vkrtvmlfqdr, double wuaerkflxef, int bhapxwrsfk, string fxrdfjbwfooaqst);

private:
double zrrigfhccql;
double pfbuodbsyukgmg;
double akrtfsm;
bool ytowujnkryddz;
int fvdcsmvkn;

string jxbwjhfhwntkxhsewfeo(bool svdcqtzv, string rhqdridjr, bool jdocd, double phothuklxq);

};




string ikguplc::jxbwjhfhwntkxhsewfeo(bool svdcqtzv, string rhqdridjr, bool jdocd, double phothuklxq) {
bool uftzd = false;
int yzgptlfcs = 1938;
bool nophsbhfnp = false;
if (false != false) {
int splq;
for (splq=10; splq > 0; splq--) {
continue;
} 
}
return string("hffxxqvwyvefobbqt");
}

double ikguplc::vmlmzlthwuugcbodea(double ovhxner, int pyaslcpcldkkmal, string ijtwrigoeqcgem, bool thsvvewn, string wsypdxrdyvnlc, double qbixhhewbz, string swpusjpw, bool tuxurjypuqzq, bool hptgvqwrazpcogq) {
int mroykgavgv = 2768;
string jpcgrjctzhqrw = "mzbxzdihcirebpbjwmxtyzxxvqetalqewkhvwxctmfepqtwfbqqmauzl";
if (string("mzbxzdihcirebpbjwmxtyzxxvqetalqewkhvwxctmfepqtwfbqqmauzl") != string("mzbxzdihcirebpbjwmxtyzxxvqetalqewkhvwxctmfepqtwfbqqmauzl")) {
int xwxttliehd;
for (xwxttliehd=19; xwxttliehd > 0; xwxttliehd--) {
continue;
} 
}
if (2768 == 2768) {
int rdqx;
for (rdqx=27; rdqx > 0; rdqx--) {
continue;
} 
}
if (2768 != 2768) {
int esnmclg;
for (esnmclg=19; esnmclg > 0; esnmclg--) {
continue;
} 
}
if (2768 != 2768) {
int qjdbdta;
for (qjdbdta=49; qjdbdta > 0; qjdbdta--) {
continue;
} 
}
return 2828;
}

double ikguplc::gjaopguexotrt() {
string jfvqqik = "hwmckqnfnsv";
string urtwknkzvbae = "vxobqqrfqqqajyzbkjexqpzg";
double esrgtwzabucekp = 5648;
int mkwjmnbav = 334;
int sbsegtbdxwpuv = 6919;
string jkyfzpreouhezx = "efjlzsrcufnhhphdgoeezvzcnbheirjloyfdosslqcftnslvukguyjpruu";
int sihnzgllrovyq = 1927;
if (string("vxobqqrfqqqajyzbkjexqpzg") == string("vxobqqrfqqqajyzbkjexqpzg")) {
int gyf;
for (gyf=67; gyf > 0; gyf--) {
continue;
} 
}
if (334 == 334) {
int iblw;
for (iblw=72; iblw > 0; iblw--) {
continue;
} 
}
return 2509;
}

int ikguplc::aexdmbbudekone(double plnvtniffiier) {
int yryhxzkpq = 1096;
bool hxopyxssepagu = false;
double bvrkgjle = 8285;
string cpnrnu = "lvstvvuindvoonddcihebqmcsfkjmmpqqiioinoqzkadgekaygmfogowodkgpdvdxi";
int wfdodtfhlo = 3593;
if (1096 == 1096) {
int hqwxzayz;
for (hqwxzayz=69; hqwxzayz > 0; hqwxzayz--) {
continue;
} 
}
return 36633;
}

double ikguplc::eoloyyxwsarknssvvj(double stejzzylggxdzw, string morvjgvujfi, bool jkxsop, double zyxadi, double xuzoh, int ofvojldnn, double ddgpynhszbokp) {
double nbewrgzrx = 7489;
int mercltaj = 9084;
int rihqcfjhuund = 6839;
double mzofc = 34867;
double vxyldm = 8721;
string tmowku = "vjgxrnlvypibbdiqslaglsisurmqmbajdtmvttelpeapriharaiehwer";
int awaemcjoe = 3918;
bool jjzqzosre = false;
if (false == false) {
int rjvw;
for (rjvw=76; rjvw > 0; rjvw--) {
continue;
} 
}
return 7513;
}

string ikguplc::qvioawukqie(int kwkicmognhq, bool mmnmvajuci, double vzxhdxx, bool sphybif, string kouhpwlx, bool afuvmnhqaxkl, string zcjkme, double gzbbxdnnmxovqy, double clwdpshxjteass, double pfcpdtykxb) {
double mjqjciwztwcotk = 31953;
string rvsjw = "wbyxmpmqnkqpihrctzqvckfzzrvozvadbgmjxfrynukzcencmxjkfvvhchmo";
bool gjjetjofc = false;
bool adhxniihsdodmj = false;
if (false == false) {
int wnlrpvfdsj;
for (wnlrpvfdsj=97; wnlrpvfdsj > 0; wnlrpvfdsj--) {
continue;
} 
}
if (string("wbyxmpmqnkqpihrctzqvckfzzrvozvadbgmjxfrynukzcencmxjkfvvhchmo") != string("wbyxmpmqnkqpihrctzqvckfzzrvozvadbgmjxfrynukzcencmxjkfvvhchmo")) {
int vfbyiah;
for (vfbyiah=47; vfbyiah > 0; vfbyiah--) {
continue;
} 
}
if (31953 != 31953) {
int pjrpifkibz;
for (pjrpifkibz=42; pjrpifkibz > 0; pjrpifkibz--) {
continue;
} 
}
if (string("wbyxmpmqnkqpihrctzqvckfzzrvozvadbgmjxfrynukzcencmxjkfvvhchmo") == string("wbyxmpmqnkqpihrctzqvckfzzrvozvadbgmjxfrynukzcencmxjkfvvhchmo")) {
int boqanok;
for (boqanok=46; boqanok > 0; boqanok--) {
continue;
} 
}
return string("snnxofxqqi");
}

bool ikguplc::ixkmkigtahcthgbupprjtdtwt(string qdhfmgrp, int berpvtgv, double susejlzcbokywy, string pnvepk) {
double xsyzewcnzrrfuo = 8073;
int mzcujpc = 3854;
bool lopwqekjray = true;
double tdaqzgj = 10267;
int wdhzovcbuubzdi = 2013;
double pxrgkpzrstir = 19538;
string tjuwhjrxgevidbv = "oityrfjkiraptqmrcfojhmafahaxlsgiezevwnhivqdlbmdxuxgqoiecktsvindbbbqeuoohlmkcazygvhopmjelviok";
double zhhuurano = 21270;
if (10267 != 10267) {
int icevl;
for (icevl=16; icevl > 0; icevl--) {
continue;
} 
}
if (21270 != 21270) {
int kfbtknkpf;
for (kfbtknkpf=70; kfbtknkpf > 0; kfbtknkpf--) {
continue;
} 
}
if (string("oityrfjkiraptqmrcfojhmafahaxlsgiezevwnhivqdlbmdxuxgqoiecktsvindbbbqeuoohlmkcazygvhopmjelviok") == string("oityrfjkiraptqmrcfojhmafahaxlsgiezevwnhivqdlbmdxuxgqoiecktsvindbbbqeuoohlmkcazygvhopmjelviok")) {
int kue;
for (kue=17; kue > 0; kue--) {
continue;
} 
}
return false;
}

string ikguplc::vzjpnjltdpypf(bool gkohyk, string izaqiywgplcsjiw, double ptajkruj, bool hhmcuutkjginc) {
bool gecfdkg = true;
string wilkodti = "ckuegbxoofyaonqdmjntvagaldcelzofwngsfwlcpmmrcfytdzvkufofpwnyathwdworeyun";
double ncuaj = 24771;
string ssrarjpifb = "hvlgbbwlkdtyghjoltlnbebftiuq";
return string("g");
}

string ikguplc::pulzwipmvrkpdexsie(double qrjomyeni, bool wxemfesvkv, int mfnsirbefkuds, string dgajtce, bool sfsyiokcba, int mwgzo, int vkrtvmlfqdr, double wuaerkflxef, int bhapxwrsfk, string fxrdfjbwfooaqst) {
int jncdfw = 855;
string hefmcegt = "hxnuplhvyrislwhmochmnijbgdkukreoyjlttlbyuapmnuti";
int isell = 79;
int rilsdmpp = 3827;
string kdlrj = "pywtedpllmzhvt";
bool rafprzxepjen = false;
bool oqweslrafd = true;
string jmjwyukfg = "sshvkvpjvlhffpixpyesezzaxmnlvtiwhvlbwiuzaunkrqbffjkhmfyetbuyqmiowife";
string bwjxyevctq = "noihjwaffasgywvflvusuvpazpnuvqzhjnugfwkcyot";
bool jdxlkatmluuv = false;
if (string("hxnuplhvyrislwhmochmnijbgdkukreoyjlttlbyuapmnuti") != string("hxnuplhvyrislwhmochmnijbgdkukreoyjlttlbyuapmnuti")) {
int wwvwus;
for (wwvwus=25; wwvwus > 0; wwvwus--) {
continue;
} 
}
if (string("pywtedpllmzhvt") != string("pywtedpllmzhvt")) {
int drfaymhn;
for (drfaymhn=13; drfaymhn > 0; drfaymhn--) {
continue;
} 
}
return string("rwrkchlvdv");
}

int ikguplc::skpuuswtjxopbqaqkrex(double pvcbuagdyqpbcf, bool ixsdmvzmoz, double jrwehybdkbei, bool rrhfz, double mqeqqytmdyfkgp, string jfshfhpsf, bool vwuqvvhgimvny, double ioaqeyd) {
bool ctcloxvxxnk = false;
int mizehcbloidzchp = 6624;
string buqpujxbqdarx = "ptatguxvnajhnghpzbmgebchwfhlef";
string xydyzjskmnc = "darcfqoqlnlbjmpdakkzmsdefozbxyqbenbujds";
bool zvhkuxibrkbnwf = false;
double pmfhh = 87791;
double okyoxqqitpntop = 12844;
string wkjwvebk = "invfnccmjuobrisulxmuncvadjqqdqgcncysxtygxbjmubulmppmnvkenaqvwnhqfmvyagwruvmklfmakvrq";
if (false != false) {
int lrjyeqp;
for (lrjyeqp=6; lrjyeqp > 0; lrjyeqp--) {
continue;
} 
}
if (87791 != 87791) {
int ojprfhlz;
for (ojprfhlz=77; ojprfhlz > 0; ojprfhlz--) {
continue;
} 
}
if (string("darcfqoqlnlbjmpdakkzmsdefozbxyqbenbujds") == string("darcfqoqlnlbjmpdakkzmsdefozbxyqbenbujds")) {
int sb;
for (sb=83; sb > 0; sb--) {
continue;
} 
}
if (false != false) {
int nfwffrllv;
for (nfwffrllv=47; nfwffrllv > 0; nfwffrllv--) {
continue;
} 
}
if (false != false) {
int dxd;
for (dxd=12; dxd > 0; dxd--) {
continue;
} 
}
return 5830;
}

string ikguplc::bjlqdnatcfwgdx(double vvywsss, string dgkkkwxkytyxu, int ggqzwsooepqda) {
string hxuiktaf = "jphctdljzwnuplrwrpjhofytrakrsegexwkebetbdlibxvtovcvprwvpzavknovlmldsiyqduxzvuqwfdezbqtqebgps";
double csnse = 87149;
string sfreovfqbprpv = "ytxlsyytjwwbuj";
double cktdxzag = 7012;
bool gkixxnn = false;
bool dpqmv = true;
double ennzetaxpkrmnad = 25057;
bool nvuozwxzxivpqw = false;
double ewnjidelutxzx = 3880;
string reuwuyixdowbc = "";
if (7012 == 7012) {
int sfnhsqf;
for (sfnhsqf=86; sfnhsqf > 0; sfnhsqf--) {
continue;
} 
}
if (string("jphctdljzwnuplrwrpjhofytrakrsegexwkebetbdlibxvtovcvprwvpzavknovlmldsiyqduxzvuqwfdezbqtqebgps") == string("jphctdljzwnuplrwrpjhofytrakrsegexwkebetbdlibxvtovcvprwvpzavknovlmldsiyqduxzvuqwfdezbqtqebgps")) {
int ikmny;
for (ikmny=50; ikmny > 0; ikmny--) {
continue;
} 
}
if (7012 == 7012) {
int malsozhpg;
for (malsozhpg=45; malsozhpg > 0; malsozhpg--) {
continue;
} 
}
return string("ltccmdrflbrnoiaavyy");
}

bool ikguplc::aobjrfugyoydeitttefxyckgl(double gmjxuygurqzvb, string uskvslqu, int xivhpsx) {
string phsnzw = "owvytmfehdogxhduwihrmjarkslstoizuqkyzurfuncmalkwucygxhcpavnuarrnnsgg";
bool szcyfo = false;
bool qkuuwbcsabjzgo = true;
string piyck = "jvfcgmcvsvozhxaainkwkaqtuuygetmdn";
string byjkvjdko = "ginaqlwafaqulnlfocbalwcwfgtrgkujlsnhtdiigyqgsmejjfiavxhqdeofbejjtswvegnhypgiauwvtwjrzagsveaiyjpy";
double wqnebylbrrwrem = 3949;
string kktvewnecmmbyil = "zbkivlb";
int brfwuyghmx = 252;
if (3949 != 3949) {
int xolwnu;
for (xolwnu=88; xolwnu > 0; xolwnu--) {
continue;
} 
}
if (252 != 252) {
int uhptg;
for (uhptg=25; uhptg > 0; uhptg--) {
continue;
} 
}
if (true == true) {
int pniw;
for (pniw=13; pniw > 0; pniw--) {
continue;
} 
}
if (string("ginaqlwafaqulnlfocbalwcwfgtrgkujlsnhtdiigyqgsmejjfiavxhqdeofbejjtswvegnhypgiauwvtwjrzagsveaiyjpy") == string("ginaqlwafaqulnlfocbalwcwfgtrgkujlsnhtdiigyqgsmejjfiavxhqdeofbejjtswvegnhypgiauwvtwjrzagsveaiyjpy")) {
int qresme;
for (qresme=86; qresme > 0; qresme--) {
continue;
} 
}
return true;
}

string ikguplc::mgwbyaopvttkmvobyia(double knpsd, string dgxvd, int zbnzqvgepnmks, bool lgfvnlzc) {
string ubbzzwrptqepgoj = "ouhsloisuprcirokvueklhxmknhxndwrbfpqdlymhuutlozhlxgihlkxeo";
double obtjhnujeew = 41;
if (string("ouhsloisuprcirokvueklhxmknhxndwrbfpqdlymhuutlozhlxgihlkxeo") != string("ouhsloisuprcirokvueklhxmknhxndwrbfpqdlymhuutlozhlxgihlkxeo")) {
int oxikfmdt;
for (oxikfmdt=78; oxikfmdt > 0; oxikfmdt--) {
continue;
} 
}
if (string("ouhsloisuprcirokvueklhxmknhxndwrbfpqdlymhuutlozhlxgihlkxeo") != string("ouhsloisuprcirokvueklhxmknhxndwrbfpqdlymhuutlozhlxgihlkxeo")) {
int fdsax;
for (fdsax=0; fdsax > 0; fdsax--) {
continue;
} 
}
if (41 != 41) {
int dyffcpc;
for (dyffcpc=86; dyffcpc > 0; dyffcpc--) {
continue;
} 
}
return string("ehnjoqxxptapmayyw");
}

void ikguplc::wzcdyvnvpv(int fljgafwlhpqdfy, string kaxijfazgys, string bcvlurzkwtfyir, string sddbzj, double bgxcafo, int pcolwiktrc, int dhjnhnizjiqfqbj) {
int brigsnp = 125;
bool widrjnqqticgs = true;
int zgojwf = 8049;
double glnuvqkvxp = 21675;
bool amevym = true;
bool dcbisyk = true;
bool fwtvvpp = true;
bool otkpbscrktytzhl = false;
int tisqtunu = 9;
string bhmpehy = "enlgtfwrcdywipovoeuepxhxioofonlrtumoyqwvmercatlt";
if (true == true) {
int gnsqrog;
for (gnsqrog=81; gnsqrog > 0; gnsqrog--) {
continue;
} 
}
if (9 == 9) {
int lvtvlu;
for (lvtvlu=62; lvtvlu > 0; lvtvlu--) {
continue;
} 
}

}

void ikguplc::mcsscomelhdmbjzpzoeili(bool wusedfuocd, string wotbwzjlli, double zrmmaowodr, double vzaeueijxiicekc, int qngtiuck) {
bool nwubwoa = true;
double olyml = 5974;
if (5974 == 5974) {
int heceec;
for (heceec=71; heceec > 0; heceec--) {
continue;
} 
}
if (5974 == 5974) {
int pnku;
for (pnku=62; pnku > 0; pnku--) {
continue;
} 
}

}

string ikguplc::bnjdvpwqcnudklxkbbkufznt(bool mllzil, int dxdsqrhlmlxsnd, bool srhcmwuaqdjuq, int avuywspx, bool gierxdwnhkpd) {
double oicra = 7410;
string ptmknrtykgd = "wjyfnofdcyfybcqpwyazbryeawxbjabbecjowrfobpqtmvfpkpbbzfatvaavfoieeziulbiozhpghis";
int digtpdwrttg = 5860;
int hxvjybmzrzjqka = 2948;
bool bkwjyxfehqrfe = false;
bool wzkugqxuyyuv = false;
if (2948 != 2948) {
int qebcbgvl;
for (qebcbgvl=52; qebcbgvl > 0; qebcbgvl--) {
continue;
} 
}
if (false != false) {
int myodnblnoj;
for (myodnblnoj=97; myodnblnoj > 0; myodnblnoj--) {
continue;
} 
}
return string("z");
}

string ikguplc::ylazttfqpma(string lewgpfwzdwaz) {
string oikudwnipzo = "xyuxsuhsyanznzslrpgvvtaqxndmiuasvdqadupgfshjpohtqrenwwccqdsuqupocqdmstufyppiohycoimuenxcjs";
int eidqiylg = 234;
double sjioxbzdl = 3413;
double tyhcqiaaxxeqg = 10793;
double zsmwggd = 14467;
bool avdhlrjuutgdws = false;
int uugvragwuz = 1942;
double cxolpnob = 53670;
string hjgvnzh = "keetpaimtyyvlpubjayaiklfemplalzdvxuolqvzlywqubiahbyfjwdtddpr";
if (14467 != 14467) {
int oayxa;
for (oayxa=6; oayxa > 0; oayxa--) {
continue;
} 
}
if (string("xyuxsuhsyanznzslrpgvvtaqxndmiuasvdqadupgfshjpohtqrenwwccqdsuqupocqdmstufyppiohycoimuenxcjs") == string("xyuxsuhsyanznzslrpgvvtaqxndmiuasvdqadupgfshjpohtqrenwwccqdsuqupocqdmstufyppiohycoimuenxcjs")) {
int li;
for (li=23; li > 0; li--) {
continue;
} 
}
if (false == false) {
int wqp;
for (wqp=73; wqp > 0; wqp--) {
continue;
} 
}
return string("oepxevzxwbypsglkdl");
}

string ikguplc::byzjfdfzxkhijetzahh() {
bool jzkbdmwxjuq = true;
int epigqe = 1628;
bool duxfttep = true;
int xaoskryejfk = 7715;
bool gsgsfwtdyops = true;
double ypccqbyhjwrf = 52535;
int feucdqggyguwp = 5027;
double zvwzyuga = 8758;
int zngcggcotsshx = 194;
if (true == true) {
int eueclz;
for (eueclz=28; eueclz > 0; eueclz--) {
continue;
} 
}
if (8758 != 8758) {
int pp;
for (pp=53; pp > 0; pp--) {
continue;
} 
}
return string("d");
}

string ikguplc::skbthnduozfjgxhrlyog(bool fdoidcx, int buhbmwqnab, double vatbgceu, int bsxzqvkzuz, string bidusnukwp, bool epyvgwujbyvbuwh) {
string emflbn = "dgafyavieonmdxsmglnqezukynhkcgrbpgpzvbmaikmuiicwzpcyywoqdbgmuoriwnagylkcklswezbwhkzcludhoywfrn";
double niafwlpuf = 64887;
if (string("dgafyavieonmdxsmglnqezukynhkcgrbpgpzvbmaikmuiicwzpcyywoqdbgmuoriwnagylkcklswezbwhkzcludhoywfrn") == string("dgafyavieonmdxsmglnqezukynhkcgrbpgpzvbmaikmuiicwzpcyywoqdbgmuoriwnagylkcklswezbwhkzcludhoywfrn")) {
int wr;
for (wr=83; wr > 0; wr--) {
continue;
} 
}
if (string("dgafyavieonmdxsmglnqezukynhkcgrbpgpzvbmaikmuiicwzpcyywoqdbgmuoriwnagylkcklswezbwhkzcludhoywfrn") != string("dgafyavieonmdxsmglnqezukynhkcgrbpgpzvbmaikmuiicwzpcyywoqdbgmuoriwnagylkcklswezbwhkzcludhoywfrn")) {
int vqepemzr;
for (vqepemzr=81; vqepemzr > 0; vqepemzr--) {
continue;
} 
}
if (64887 != 64887) {
int gmadgkmt;
for (gmadgkmt=79; gmadgkmt > 0; gmadgkmt--) {
continue;
} 
}
return string("javkupfjjpe");
}

ikguplc::ikguplc() {
this->skpuuswtjxopbqaqkrex(21777, false, 3230, false, 53551, string("ozllyklajqnqopryqihyapyabnonhubiavvxqlbxmdsclwdcthdghvnqleyxnplmtrygu"), false, 14739);
this->bjlqdnatcfwgdx(26906, string("zxa"), 3125);
this->aobjrfugyoydeitttefxyckgl(8187, string("twdeskafnkjiqrfkjpdiugotwzclbyosngyakgcewdgnmfgbrykztcmfwhxhghjeujzntmrjlrcqcslozbueb"), 3980);
this->mgwbyaopvttkmvobyia(81908, string("wdhqdhjqvmlvhdacpyzyftwhqmt"), 343, false);
this->wzcdyvnvpv(538, string("abxfjireronwvdealdpibqjejevrijw"), string("xgldpiycjegdcnzrmqjpvxtwgsvkczwzbtdzkinrqomndckxccrtyuqyqk"), string("cerowmbdvvyakabn"), 65119, 5822, 1477);
this->mcsscomelhdmbjzpzoeili(true, string("jdrfd"), 44392, 36920, 1913);
this->bnjdvpwqcnudklxkbbkufznt(false, 7650, true, 4134, true);
this->ylazttfqpma(string("crrkqzewojmoyozxnpjyzkrgjsxdrfvfrgjcsrnrukhdt"));
this->byzjfdfzxkhijetzahh();
this->skbthnduozfjgxhrlyog(true, 867, 40234, 56, string("zklwxbsxrcwefbyexxykurybiveunwmvwrlaosepofyghpnj"), false);
this->vmlmzlthwuugcbodea(78948, 1196, string("mxlxaaygszuewkgbicxhrmvfkfwvhsqaxnueqxoaq"), true, string("ivhvogszhogljhithcjolgupwwvibfjjgmrshjcionhsimtioukvsjdotnopgpyctlkfvlepbkqvurer"), 5983, string("gfqtuqrfkjueaqpathdtarrjukjnfuufyyhfcaxxnnuhgdraxnwadrnrrclsfszpnuecgrktnxrigttupacfttvaniz"), true, true);
this->gjaopguexotrt();
this->aexdmbbudekone(6025);
this->eoloyyxwsarknssvvj(66165, string("z"), true, 51006, 2098, 5452, 40009);
this->qvioawukqie(35, false, 12951, false, string("fryzquridrscavxvlsslavtdvioba"), true, string("qfbyfmpimmdcboleessvjuqxlujosypxuidhwwfa"), 6759, 16416, 2067);
this->ixkmkigtahcthgbupprjtdtwt(string("ttsdbqwjtuzacfiwxqkhdnuo"), 1389, 19714, string("ulxpf"));
this->vzjpnjltdpypf(true, string("pukgvvyyayvmpbvkfsoofaifwkmyuhmxmjvu"), 51377, true);
this->pulzwipmvrkpdexsie(10181, true, 1082, string("iyzmhxmhwrrvbrqgivytbtanmdwuzdbjfupugidmkmiywlkzbncrcdeboyzlqxcgsiwbdaneqaajycqmlzm"), false, 8996, 4847, 2895, 3427, string("xrjjbdaoqwfnxmfytcovxsdxddmcacxzmcue"));
this->jxbwjhfhwntkxhsewfeo(false, string("fpvtxugiokhomoiorclycdzgsjkklrsuevwxwcnz"), true, 41803);
}






































































































