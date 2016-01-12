# Heating Model
Give inventory of contents of heating model configuration file.

## `Heating_Model/config/heating_model.cfg`

| Variable Target | Type | Description |
|:---------------:|:---- |:-----------|
| `fDuration` | float | Total duration of the heating phase (in s) |
| `s0quiescent` | float | Location of background heating (in cm) |
| `sHquiescent` | float | Spread of background heating (in cm); infinity corresponds to uniform heating |
| `E0quiescent` | float | Strength of background heating (in erg cm<sup>-3</sup> s<sup>-1</sup>) |
| `NumActivatedEvents` | int | Number of time-dependent heating events |
| `s0episodic` | float | Location of _i_<sup>th</sup> event (in cm) |
| `sHepisodic` | float | Spread of _i_<sup>th</sup> event (in cm); infinity corresponds to uniform heating |
| `E0episodic` | float | Strength of _i_<sup>th</sup> event (in erg cm<sup>-3</sup> s<sup>-1</sup>) |
| `tsRepisodic` | float | start of the rise phase of the _i_<sup>th</sup> event (s) |
| `teRepisodic` | float | end of the rise phase of the _i_<sup>th</sup> event (s) |
| `tsDepisodic` | float | start of the decay phase of the _i_<sup>th</sup> event (s) |
| `teDepisodic` | float | end of the decay phase of the _i_<sup>th</sup> event (s)|

The last seven entries of the table are repeated `NumActivatedEvents` times, where all the information for the _i_<sup>th</sup> event is on a single line. Additionally, all of the information for the background heating is also on a single line.

## _VAL_ heating model
If the optically thick option is selected, the heating model reads a VAL heating config file from the `OpticallyThick` directory in the atomic database. We will need to find a way around this when the time comes. Maybe just pass the filename via the normal config file and then make the VAL data a separate list within the config file or something. Probably easier just to pass the path to the optically thick heating config file via the standard heating config file. 