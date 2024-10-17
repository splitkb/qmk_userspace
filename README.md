# Splitkb Vial Userspace

This is the splitkb userspace repository which allows for an external set of Vial keymaps with halcyon modules to be defined and compiled. This is useful for users who want to maintain their own keymaps without having to fork the splitkb QMK or vial repository.

If you want to compile firmware without any modules you can also use the [main qmk_userspace repo](https://github.com/qmk/qmk_userspace).

If the keyboard has not been merged yet to the main branch of QMK you may need to edit the workflow, for that see [Extra info](#extra-info)

## Howto configure your build targets

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. Enable userspace in QMK config using `qmk config user.overlay_dir="$(realpath qmk_userspace)"`
1. Add a new keymap for your board using `qmk new-keymap`
    * This will create a new keymap in the `keyboards` directory, in the same location that would normally be used in the main QMK repository. For example, if you wanted to add a keymap for the Halcyon Kyria, it will be created in `keyboards/splitkb/halcyon/kyria/<your keymap name>`
    * You can also create a new keymap using `qmk new-keymap -kb <your_keyboard> -km <your_keymap>`
    * Alternatively, add your keymap manually by placing it in the location specified above. This may be easier if you want to copy the default keymap and change it to your liking.
    * `layouts/<layout name>/<your keymap name>/keymap.*` is also supported if you prefer the layout system but has not been tested with our halcyon modules.
1. Create and add `USER_NAME := halcyon_modules` to your keymaps `rules.mk`
1. Add your keymap(s) to the build by running `qmk userspace-add -kb <your_keyboard> -km <your_keymap> -e <halcyon_module>=1 -e TARGET=<filename>`.
    * This will automatically update your `qmk.json` file
    * Corresponding `qmk userspace-remove -kb <your_keyboard> -km <your_keymap> -e <halcyon_module>=1 -e TARGET=<filename>`.
    * Listing the build targets can be done with with `qmk userspace-list`
    * If you want to use a module:
        * For the filename make it so you can differentiate between the different firmwares for the modules. `kyria_rev4_default_encoder` for example.
        * The following options are available for the halcyon modules:
            * HLC_NONE, If you don't have a module installed but you do have a module on the other half.
            * HLC_ENCODER, If you have an encoder module installed.
            * HLC_TFT_DISPLAY, If you have a tft rgb display installed.
            * HLC_CIRQUE_TRACKPAD, If you have a Cirque trackpad installed.
1. Commit your changes


## Howto build with GitHub

1. In the GitHub Actions tab, enable workflows
1. Push your changes above to your forked GitHub repository
1. Look at the GitHub Actions for a new actions run
1. Wait for the actions run to complete
1. Inspect the Releases tab on your repository for the latest firmware build


## Howto build locally

1. Run the normal `qmk setup` procedure if you haven't already done so -- see [QMK Docs](https://docs.qmk.fm/#/newbs) for details.
1. Fork this repository
1. Clone your fork to your local machine
1. `cd` into this repository's clone directory
1. Set global userspace path: `qmk config user.overlay_dir="$(realpath .)"` -- you MUST be located in the cloned userspace location for this to work correctly
    * This will be automatically detected if you've `cd`ed into your userspace repository, but the above makes your userspace available regardless of your shell location.
1. Compile normally: `qmk compile -kb your_keyboard -km your_keymap -e <your_module>=1 -e TARGET=<filename>` or `make your_keyboard:your_keymap -e <your_module>=1 -e TARGET=<filename>`

Alternatively, if you configured your build targets above, you can use `qmk userspace-compile` to build all of your userspace targets at once.


## Extra info

If you wish to point GitHub actions to a different repository, a different branch, or even a different keymap name, you can modify `.github/workflows/build_binaries.yml` to suit your needs.

To override the `build` job, you can change the following parameters to use a different QMK repository or branch, this can be useful if you want to use a different QMK or vial branch for example:
```
    with:
      qmk_repo: splitkb/vial_qmk
      qmk_ref: halcyon-kyria
```

If you wish to manually manage `qmk_firmware` using git within the userspace repository, you can add `qmk_firmware` as a submodule in the userspace directory instead. GitHub Actions will automatically use the submodule at the pinned revision if it exists, otherwise it will use the default latest revision of `qmk_firmware` from the main repository. This will not work when using vial.

This can also be used to control which fork is used.

1. (First time only) `git submodule add https://github.com/qmk/qmk_firmware.git`
1. (To update) `git submodule update --init --recursive`
1. Commit your changes to your userspace repository
