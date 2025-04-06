import React from 'react';
import { BrowserRouter as Router, Routes, Route, Navigate } from 'react-router-dom';
import { Provider } from 'react-redux';
import store from './store/store';
import Header from './components/Header';
import AddCandidate from './pages/AddCandidate';
import ExistingApplications from './components/ExistingApplications';

const App = () => {
  return (
    <Provider store={store}>
      <Router>
        <div className="min-h-screen h-screen flex flex-col bg-gray-100">
          <Header />
          <main className="flex-1 flex flex-col overflow-auto">
            <Routes>
              <Route path="/add-new-candidate" element={<AddCandidate />} />
              <Route path="/existing-applications" element={<ExistingApplications />} />
              <Route path="*" element={<Navigate to="/add-new-candidate" replace />} />
            </Routes>
          </main>

        </div>
      </Router>
    </Provider>
  );
};

export default App;