# Motif Classic

This project is a new effort to address portability issues and defects
within Motif, the industry standard widget library for X11.

## Installation

Please see the file RELNOTES for release notes on how to build and
install this product.

## Why 2.1.30 instead of the 2.3 release hosted on SourceForge?

Unfortunately, the widgets added in Open Motif 2.2 and later Motif 2.3
were hasty conversions of proprietary vendor addons to Motif 1.2. They
have a number of issues that render them unsafe in mission critical
contexts, including being thread unsafe.

For more details, see [IST's comprehensive analysis][1] of the design
flaws in these later releases.

Other problems include:
* Binary compatibility with the Motif 2.1 series was broken.
* Support for imake was removed and the release notes only claim testing on
  Linux. Recent releases of the GNU autotools suite have broken compatibility
  with the Motif and CDE reference platforms, all based on System V Release 4.

[1]: http://www.motifdeveloper.com/tips/Motif22Review.pdf