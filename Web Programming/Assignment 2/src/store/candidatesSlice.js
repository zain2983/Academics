
// src/store/candidateSlice.js
import { createSlice } from '@reduxjs/toolkit';

const candidateSlice = createSlice({
  name: 'candidates',
  initialState: [],
  reducers: {
    addCandidate: (state, action) => {
      state.push(action.payload);
    }
  }
});

export const { addCandidate } = candidateSlice.actions;
export default candidateSlice.reducer;