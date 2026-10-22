# Analysing a system of stellar binaries

Many stellar systems on the night sky exist in binaries.
Each binary system consists of two stars of differing stellar masses.
However, we only the she luminosities coming from the stars.
This means that if a star is in a binary tight enough so we cannot resolve it, we also only see the sum of the fluxes that reach us, not the sum of the masses.
In the following exercise, you will compute the apparent masses for a stellar cluster full of unresolved binaries and compare them to their actual total masses.
The stellar masses come from nBody6 models [Aarseth (1999)](https://ui.adsabs.harvard.edu/abs/1999PASP..111.1333A/abstract).
The mass luminosity relation is taken from [Kroupa et al. (1993)](https://ui.adsabs.harvard.edu/abs/1993MNRAS.262..545K/abstract).

## Part 1: Reading the files

In the files subdirectory you can find four files:

* the file The_mass_Mv_data_in_AppA_KTG93.dat contains the mass-luminosity relation
    * the first column contains the bolometric magnitudes (careful, bolometric magnitudes are not luminosities, for a conversion check [here](https://en.wikipedia.org/wiki/Absolute_magnitude#Bolometric_magnitude))
    * the second column contains the stellar masses in solar masses
* the files SC100Myr.dat, SC200Myr.dat and SC300Myr.dat contain the stellar masses taken from a simulated cluster at different ages
    * all values are given in solar masses
    * lines that contain a single value give the mass of a single star
    * lines that contain two values contain the stellar masses of the components of a binary

In part 1 your task is to read in those files.
Define one or multiple data structures, with which the program is to work and write the data onto these structures.
Document and test your code.

## Part 2: Doing the calculations

Your job is to compute, how an observer that cannot resolve the binaries in the stellar cluster would see it.
To this end, use the mass-luminosity relation to transform the stellar masses of binary components into luminosities (check carefully if the magnitudes read in in the previous part have already been transformed into solar luminosities).
Add the luminosities up.
Then transform the resulting luminosity back into the apparent single star an observer believes to see.
Add everything to the data structures from part 1 (you are allowed to add any elements you need).
Document and test your code.

## Part 3: Plotting the results

Now that everything is computed it is time to visualize the results!
Take the results of Part 2 and make one or more plots that shows the differences between the apparent and total masses of the individual binaries.
Document and test your code.
