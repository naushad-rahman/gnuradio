/* -*- c++ -*- */
/*
 * Copyright 2010 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_GRI_FFT_FILTER_H
#define INCLUDED_GRI_FFT_FILTER_H

#include <gr_complex.h>
#include <vector>

class gri_fft_real_fwd;
class gri_fft_real_rev;

class gri_fft_filter
{
 private:
  int			   d_ntaps;
  int			   d_nsamples;
  int			   d_fftsize;		// fftsize = ntaps + nsamples - 1
  int                      d_decimation;
  gri_fft_real_fwd	  *d_fwdfft;		// forward "plan"
  gri_fft_real_rev	  *d_invfft;		// inverse "plan"
  std::vector<float>       d_tail;		// state carried between blocks for overlap-add
  std::vector<gr_complex>  d_xformed_taps;	// Fourier xformed taps
  std::vector<float>	   d_new_taps;

  void compute_sizes(int ntaps);
  int tailsize() const { return d_ntaps - 1; }
  
 public:
  gri_fft_filter (int decimation, const std::vector<float> &taps);
  ~gri_fft_filter ();

  int set_taps (const std::vector<float> &taps);
  
  int filter (int nitems, const float *input, float *output);

};

#endif /* INCLUDED_GRI_FFT_FILTER_H */
