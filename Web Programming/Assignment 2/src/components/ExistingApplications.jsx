// src/components/ExistingApplications.jsx
import React, { useState } from 'react';
import { useSelector } from 'react-redux';

const ExistingApplications = () => {
  const candidates = useSelector(state => state.candidates);
  const [searchTerm, setSearchTerm] = useState('');
  
  const handleSearch = (e) => {
    setSearchTerm(e.target.value);
  };
  
  const filteredCandidates = candidates.filter(candidate => {
    if (!searchTerm.trim()) return true;
    
    const searchLower = searchTerm.toLowerCase();
    return (
      candidate.name.toLowerCase().includes(searchLower) ||
      candidate.appliedFor.toLowerCase().includes(searchLower) ||
      candidate.skills.some(skill => skill.toLowerCase().includes(searchLower))
    );
  });

  // Default placeholder image if no profile image is available
  const defaultProfileImage = 'https://via.placeholder.com/60x60';
  
  // Handle image loading error
  const handleImageError = (e) => {
    console.log('Image failed to load, using fallback');
    e.target.onerror = null; // Prevent infinite error loop
    e.target.src = defaultProfileImage;
  };
  
  return (
    <div className="flex-1 flex flex-col container mx-auto p-4 sm:p-6">
      <h2 className="text-2xl sm:text-3xl font-semibold mb-6 text-gray-800 text-center sm:text-left">
        Existing Applications
      </h2>
      
      <div className="mb-6 max-w-md mx-auto">
        <input
          type="text"
          placeholder="Search"
          value={searchTerm}
          onChange={handleSearch}
          className="w-full px-4 py-2 text-base sm:text-lg border rounded-md shadow-md focus:outline-none focus:ring-2 focus:ring-blue-500 transition duration-200 ease-in-out"
        />
      </div>
      
      {filteredCandidates.length === 0 ? (
        <div className="flex-1 flex items-center justify-center">
          <div className="bg-white shadow-md rounded-lg p-6 text-center">
            <p className="text-gray-500">No candidates found. Add new candidates or adjust your search.</p>
          </div>
        </div>
      ) : (
        <div className="flex-1 overflow-y-auto">
          <div className="grid grid-cols-1 sm:grid-cols-2 lg:grid-cols-3 gap-4 sm:gap-6 lg:gap-8 pb-6">
            {filteredCandidates.map(candidate => (
              <div key={candidate.id} className="bg-white shadow-lg rounded-lg overflow-hidden hover:shadow-xl transition-shadow duration-300 ease-in-out">
                <div className="bg-blue-600 text-white p-4 sm:p-6 flex flex-col sm:flex-row items-center sm:items-start">
                  <img 
                    src={candidate.profileImageUrl || defaultProfileImage} 
                    alt={candidate.name} 
                    className="w-16 h-16 object-cover rounded-full border-2 border-white mb-3 sm:mb-0 sm:mr-6"
                    onError={handleImageError}
                  />
                  <div className="text-center sm:text-left">
                    <h3 className="font-semibold text-lg sm:text-xl">{candidate.name}</h3>
                    <p className="text-sm">{candidate.appliedFor}</p>
                  </div>
                </div>
                
                <div className="p-4 sm:p-6">
                  <div className="mb-4">
                    <p className="text-sm text-gray-500 mb-2">Skills:</p>
                    <div className="flex flex-wrap gap-2 mt-1">
                      {candidate.skills.map((skill, index) => (
                        <span 
                          key={index}
                          className="bg-blue-100 text-blue-800 text-xs px-3 py-1 rounded-full"
                        >
                          {skill}
                        </span>
                      ))}
                    </div>
                  </div>
                </div>
              </div>
            ))}
          </div>
        </div>
      )}
    </div>
  );
};

export default ExistingApplications;
