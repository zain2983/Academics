// src/store/store.js
import { configureStore } from '@reduxjs/toolkit';
import candidateReducer from './candidatesSlice';

const store = configureStore({
  reducer: {
    candidates: candidateReducer
  }
});

export default store;