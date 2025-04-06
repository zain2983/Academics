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
  
  const formatDate = (dateString) => {
    const date = new Date(dateString);
    return new Intl.DateTimeFormat('en-US', {
      year: 'numeric',
      month: 'short',
      day: 'numeric'
    }).format(date);
  };
  
  return (
    <div className="container mx-auto p-4">
      <h2 className="text-2xl font-bold mb-6">Existing Applications</h2>
      
      <div className="mb-6">
        <input
          type="text"
          placeholder="Search by name, position or skills..."
          value={searchTerm}
          onChange={handleSearch}
          className="shadow appearance-none border border-gray-300 rounded w-full py-2 px-3 text-gray-700 leading-tight focus:outline-none focus:shadow-outline"
        />
      </div>
      
      {filteredCandidates.length === 0 ? (
        <div className="bg-white shadow-md rounded p-6 text-center">
          <p className="text-gray-500">No candidates found. Add new candidates or adjust your search.</p>
        </div>
      ) : (
        <div className="grid grid-cols-1 md:grid-cols-2 lg:grid-cols-3 gap-6">
          {filteredCandidates.map(candidate => (
            <div key={candidate.id} className="bg-white shadow-md rounded overflow-hidden">
              <div className="bg-blue-600 text-white p-4 flex items-center">
                <img 
                  src={candidate.profileImageUrl || '/api/placeholder/60/60'} 
                  alt={candidate.name} 
                  className="w-12 h-12 object-cover rounded-full mr-4"
                />
                <div>
                  <h3 className="font-bold text-lg">{candidate.name}</h3>
                  <p className="text-sm">{candidate.appliedFor}</p>
                </div>
              </div>
              
              <div className="p-4">
                <div className="mb-3">
                  <p className="text-sm text-gray-600">Contact Information:</p>
                  <p className="text-sm">{candidate.email}</p>
                  <p className="text-sm">{candidate.phone}</p>
                </div>
                
                <div className="mb-3">
                  <p className="text-sm text-gray-600">Skills:</p>
                  <div className="flex flex-wrap gap-1 mt-1">
                    {candidate.skills.map((skill, index) => (
                      <span 
                        key={index}
                        className="bg-blue-100 text-blue-800 text-xs px-2 py-1 rounded"
                      >
                        {skill}
                      </span>
                    ))}
                  </div>
                </div>
                
                <div className="mb-3">
                  <p className="text-sm text-gray-600">Experience:</p>
                  <p className="text-sm line-clamp-3">{candidate.experience}</p>
                </div>
                
                <div className="text-right text-xs text-gray-500">
                  Applied on: {formatDate(candidate.appliedDate)}
                </div>
              </div>
            </div>
          ))}
        </div>
      )}
    </div>
  );
};

export default ExistingApplications;