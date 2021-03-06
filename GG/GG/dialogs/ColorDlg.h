//! GiGi - A GUI for OpenGL
//!
//!  Copyright (C) 2003-2008 T. Zachary Laine <whatwasthataddress@gmail.com>
//!  Copyright (C) 2013-2020 The FreeOrion Project
//!
//! Released under the GNU Lesser General Public License 2.1 or later.
//! Some Rights Reserved.  See COPYING file or https://www.gnu.org/licenses/lgpl-2.1.txt
//! SPDX-License-Identifier: LGPL-2.1-or-later

//! @file GG/dialogs/ColorDlg.h
//!
//! Contains the Wnd class, upon which all GG GUI elements are based.

#ifndef _GG_dialogs_ColorDlg_h_
#define _GG_dialogs_ColorDlg_h_


#include <GG/Button.h>
#include <GG/ClrConstants.h>


namespace GG {

class Font;
template <typename T>
class Slider;

/** \brief Contains the necessary data to represent a color in HSV space, with
    an alpha value thrown in to make conversions to and from GG::Clr
    possible. */
struct GG_API HSVClr
{
    HSVClr();

    HSVClr(double h_, double s_, double v_, GLubyte a_ = 255);

    double  h;   ///< hue
    double  s;   ///< saturation
    double  v;   ///< value
    GLubyte a;   ///< alpha
};

/** \brief A control specifically designed for ColorDlg that allows the user
    to select a point in the Hue-Saturation subspace of the HSV color
    space. */
class GG_API HueSaturationPicker : public Control
{
public:
    /** emitted whenever the hue or saturation in the picker changes */
    typedef boost::signals2::signal<void (double, double)> ChangedSignalType;

    HueSaturationPicker(X x, Y y, X w, Y h);

    void Render() override;

    void LButtonDown(const Pt& pt, Flags<ModKey> mod_keys) override;

    void LDrag(const Pt& pt, const Pt& move, Flags<ModKey> mod_keys) override;

    void SetHueSaturation(double hue, double saturation); ///< sets the current hue and saturation.  Note that this does not cause a signal to be emitted.

    mutable ChangedSignalType ChangedSignal; ///< emitted whenever the hue or saturation in the picker changes

private:
    void SetHueSaturationFromPt(Pt pt);

    double m_hue;
    double m_saturation;
    std::vector<std::vector<std::pair<double, double>>> m_vertices;
    std::vector<std::vector<Clr>>                       m_colors;
};


/** \brief A control specifically designed for ColorDlg that allows the user
    to select a point in the Value subspace of the HSV color space. */
class GG_API ValuePicker : public Control
{
public:
    /** emitted whenever the hue or saturation in the picker changes */
    typedef boost::signals2::signal<void (double)> ChangedSignalType;

    ValuePicker(X x, Y y, X w, Y h, Clr arrow_color);

    void Render() override;
    void LButtonDown(const Pt& pt, Flags<ModKey> mod_keys) override;
    void LDrag(const Pt& pt, const Pt& move, Flags<ModKey> mod_keys) override;

    /** Sets the current hue and saturation.  These are only used to render
        the control, and do not otherwise influence its operation. */
    void SetHueSaturation(double hue, double saturation);
    void SetValue(double value); ///< sets the current value.  Note that this does not cause a signal to be emitted.

    mutable ChangedSignalType ChangedSignal; ///< emitted whenever the hue or saturation in the picker changes

private:
    void SetValueFromPt(Pt pt);

    double  m_hue;
    double  m_saturation;
    double  m_value;

    Clr m_arrow_color;
};


/** \brief A dialog box used to get a color selection from the user.

    The user may select a certain number of custom colors, which will remain
    available for the duration of that run of the application in the
    ColorDlg's static space.  If desired, an optional previous color can be
    provided to the ColorDlg ctor, which will cause this previous color to be
    shown next to the new color for comparison purposes. */
class GG_API ColorDlg : public Wnd
{
public:
    /** \brief The button used to select the custom colors in ColorDlg. */
    class GG_API ColorButton : public Button
    {
    public:
        ColorButton(const Clr& color);

        /** returns the custom color represented by the button */
        Clr RepresentedColor() const;

        /** sets the custom color represented by the button */
        void SetRepresentedColor(const Clr& color);

    protected:
        void RenderUnpressed() override;
        void RenderPressed() override;
        void RenderRollover() override;

    private:
        Clr m_represented_color;
    };

    /** \brief A simple control that only displays a rectangle filled with the
        given color.

        The color is shown in full alpha in the upper-left portion of the
        rectangle, and the color is shown in its given alpha in the lower-left
        of the rectangle. */
    class GG_API ColorDisplay : public Control
    {
    public:
        ColorDisplay(Clr color);

        void Render() override;
    };

    ColorDlg(X x, Y y, Clr original_color, const std::shared_ptr<Font>& font,
             Clr dialog_color, Clr border_color, Clr text_color = CLR_BLACK);
    void CompleteConstruction() override;

    /** Returns true iff the user selected a color and then clicked the "Ok"
        button.  Otherwise, the color returned by Result() will be the
        original color if one was selected, or undefined if one was not. */
    bool ColorWasSelected() const;

    /** returns the color selected by the user, if the "Ok" button was used to close the dialog. */
    Clr Result() const;

    void Render() override;
    void KeyPress(Key key, std::uint32_t key_code_point, Flags<ModKey> mod_keys) override;

    static const std::size_t INVALID_COLOR_BUTTON;

private:
    enum {R, G, B, A, H, S, V};

    void ColorChanged(HSVClr color);
    void HueSaturationPickerChanged(double hue, double saturation);
    void ValuePickerChanged(double value);
    void UpdateRGBSliders();
    void UpdateHSVSliders();
    void ColorChangeFromRGBSlider();
    void ColorButtonClicked(std::size_t i);
    void RedSliderChanged(int value, int low, int high);
    void GreenSliderChanged(int value, int low, int high);
    void BlueSliderChanged(int value, int low, int high);
    void AlphaSliderChanged(int value, int low, int high);
    void HueSliderChanged(int value, int low, int high);
    void SaturationSliderChanged(int value, int low, int high);
    void ValueSliderChanged(int value, int low, int high);
    void OkClicked();
    void CancelClicked();

    HSVClr  m_current_color;
    Clr     m_original_color;
    bool    m_original_color_specified = true;
    bool    m_color_was_picked = false;

    std::shared_ptr<HueSaturationPicker>      m_hue_saturation_picker;
    std::shared_ptr<ValuePicker>              m_value_picker;
    std::shared_ptr<Layout>                   m_pickers_layout;
    std::shared_ptr<ColorDisplay>             m_new_color_square;
    std::shared_ptr<ColorDisplay>             m_old_color_square;
    std::shared_ptr<TextControl>              m_new_color_square_text;
    std::shared_ptr<TextControl>              m_old_color_square_text;
    std::shared_ptr<Layout>                   m_color_squares_layout;
    std::vector<std::shared_ptr<ColorButton>> m_color_buttons;
    std::shared_ptr<Layout>                   m_color_buttons_layout;
    std::size_t                               m_current_color_button;
    std::vector<std::shared_ptr<TextControl>> m_slider_labels;
    std::vector<std::shared_ptr<TextControl>> m_slider_values;
    std::vector<std::shared_ptr<Slider<int>>> m_sliders;
    std::shared_ptr<Button>                   m_ok;
    std::shared_ptr<Button>                   m_cancel;
    std::shared_ptr<Layout>                   m_sliders_ok_cancel_layout;

    Clr m_color;
    Clr m_border_color;
    Clr m_text_color;

    static std::vector<Clr>   s_custom_colors;
};

}


#endif
