## 2024-02-17

Install Pico SDK from the usual place. I'm not too happy about this "installs everything" installer. Seems ok if you just want to work with the Pico, not so great if you already have a dev environment.

After messing around with the pico-examples workspace, I copied a few files over to this repo.

Launch "Pico - Visual Studio Code". Open the repo folder. In the CMake tab on the left, find "seg25_puzzle" in the "Project Outline" pane. Click the build icon.

Plug in the pico while pressing the BOOTSEL button. Windows should detect a drive. Copy `build/firmware/seg25_puzzle/test.uf2` to the drive. The pico will run the program.
