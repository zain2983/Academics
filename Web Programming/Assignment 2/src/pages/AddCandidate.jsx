import React, { useState } from "react";
import { useDispatch } from "react-redux";
import { v4 as uuidv4 } from "uuid";
import { addCandidate } from "../store/candidatesSlice";

const AddCandidate = () => {
  const dispatch = useDispatch();
  const [name, setName] = useState("");
  const [appliedFor, setAppliedFor] = useState("");
  const [skills, setSkills] = useState([""]);
  const [error, setError] = useState("");
  const [imageFile, setImageFile] = useState(null);
  const [imageUrl, setImageUrl] = useState("");
  const [uploading, setUploading] = useState(false);
  const [uploadError, setUploadError] = useState("");

  const handleSkillChange = (index, value) => {
    const newSkills = [...skills];
    newSkills[index] = value;
    setSkills(newSkills);
  };

  const addSkill = () => setSkills([...skills, ""]);
  const removeSkill = (index) => setSkills(skills.filter((_, i) => i !== index));

  const handleImageChange = (e) => {
    if (e.target.files && e.target.files[0]) {
      setImageFile(e.target.files[0]);
      // Create a preview URL for display
      const objectUrl = URL.createObjectURL(e.target.files[0]);
      setImageUrl(objectUrl);
      // Clear any previous upload errors
      setUploadError("");
    }
  };

  const uploadImageToImgBB = async () => {
    if (!imageFile) return null;
    
    setUploading(true);
    setUploadError("");
    
    try {
      const formData = new FormData();
      formData.append('image', imageFile);
      
      // Using the correct API key
      const response = await fetch('https://api.imgbb.com/1/upload?key=ec2fc100ddf7945494ea2e074c03dae1', {
        method: 'POST',
        body: formData,
      });
      
      const data = await response.json();
      
      if (data.success) {
        console.log('Image upload successful:', data.data);
        setUploading(false);
        // Return the direct display URL
        return data.data.display_url;
      } else {
        console.error('Image upload failed:', data.error);
        setUploadError("Failed to upload image: " + (data.error?.message || "Unknown error"));
        setUploading(false);
        return null;
      }
    } catch (error) {
      console.error('Error uploading image:', error);
      setUploadError("Error uploading image: " + error.message);
      setUploading(false);
      return null;
    }
  };

  const handleSubmit = async (e) => {
    e.preventDefault();
    if (!name || !appliedFor || skills.some((skill) => !skill)) {
      setError("All fields are required.");
      return;
    }
    
    setUploading(true);
    setError("");
    
    try {
      // Upload image if one is selected
      let profileImageUrl = null;
      if (imageFile) {
        profileImageUrl = await uploadImageToImgBB();
        if (!profileImageUrl && uploadError) {
          setUploading(false);
          return; // Stop form submission if image upload failed
        }
      }
      
      const candidate = {
        id: uuidv4(),
        name,
        appliedFor,
        skills,
        profileImageUrl
      };
      
      dispatch(addCandidate(candidate));
      
      // Reset form
      setName("");
      setAppliedFor("");
      setSkills([""]);
      setImageFile(null);
      setImageUrl("");
      setError("");
      setUploadError("");
    } catch (error) {
      setError("Failed to submit form: " + error.message);
    } finally {
      setUploading(false);
    }
  };

  return (
    <div className="flex-1 flex items-center justify-center p-4 sm:p-6 md:p-8">
      <form onSubmit={handleSubmit} className="w-full max-w-md bg-white shadow-lg rounded-lg p-4 sm:p-6">
        <h2 className="text-xl sm:text-2xl font-semibold text-center mb-4 sm:mb-6">Add New Candidate</h2>
        {error && <p className="text-red-600 mb-4 text-center text-sm">{error}</p>}
        
        <div className="mb-4">
          <label className="block text-gray-700 text-sm font-bold mb-2">
            Profile Image
          </label>
          <div className="flex flex-col sm:flex-row items-center space-y-3 sm:space-y-0 sm:space-x-4">
            {imageUrl && (
              <div className="relative w-20 h-20 flex-shrink-0">
                <img 
                  src={imageUrl} 
                  alt="Profile preview" 
                  className="w-20 h-20 rounded-full object-cover border border-gray-300"
                />
              </div>
            )}
            <input
              type="file"
              accept="image/*"
              onChange={handleImageChange}
              className="block w-full text-sm text-gray-500
                file:mr-4 file:py-2 file:px-4
                file:rounded-full file:border-0
                file:text-sm file:font-semibold
                file:bg-blue-50 file:text-blue-600
                hover:file:bg-blue-100"
            />
          </div>
          {uploadError && <p className="text-red-500 text-xs mt-1">{uploadError}</p>}
        </div>
        
        <div className="mb-4">
          <label htmlFor="candidate-name" className="block text-gray-700 text-sm font-bold mb-2">
            Name
          </label>
          <input
            id="candidate-name"
            type="text"
            placeholder="Enter candidate name"
            value={name}
            onChange={(e) => setName(e.target.value)}
            className="block w-full p-2 sm:p-3 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 text-sm sm:text-base"
          />
        </div>
        
        <div className="mb-4">
          <label htmlFor="candidate-role" className="block text-gray-700 text-sm font-bold mb-2">
            Role
          </label>
          <select
            id="candidate-role"
            value={appliedFor}
            onChange={(e) => setAppliedFor(e.target.value)}
            className="block w-full p-2 sm:p-3 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 text-sm sm:text-base"
          >
            <option value="">Select Role</option>
            <option value="Frontend Developer">Frontend Developer</option>
            <option value="Backend Developer">Backend Developer</option>
            <option value="Data Scientist">Data Scientist</option>
            <option value="DevOps Engineer">DevOps Engineer</option>
            <option value="UX/UI Designer">UX/UI Designer</option>
          </select>
        </div>
        
        <div className="mb-4">
          <label className="block text-gray-700 text-sm font-bold mb-2">
            Skills
          </label>
          {skills.map((skill, i) => (
            <div key={i} className="flex items-center gap-2 mb-3">
              <input
                type="text"
                placeholder={`Skill ${i + 1}`}
                value={skill}
                onChange={(e) => handleSkillChange(i, e.target.value)}
                className="flex-1 p-2 sm:p-3 border border-gray-300 rounded-lg focus:ring-2 focus:ring-blue-500 text-sm sm:text-base"
              />
              <button
                type="button"
                onClick={() => removeSkill(i)}
                className="text-red-600 hover:text-red-800 transition duration-200 text-sm whitespace-nowrap px-2 py-1"
                disabled={skills.length === 1}
              >
                Remove
              </button>
            </div>
          ))}
          <button
            type="button"
            onClick={addSkill}
            className="text-blue-600 hover:text-blue-800 mb-4 text-sm font-medium"
          >
            + Add More Skills
          </button>
        </div>
        
        <button
          type="submit"
          disabled={uploading}
          className="w-full bg-blue-600 text-white py-2 sm:py-3 rounded-lg hover:bg-blue-700 transition duration-200 disabled:bg-blue-400 text-sm sm:text-base font-medium"
        >
          {uploading ? "Uploading..." : "Submit"}
        </button>
      </form>
    </div>
  );
};

export default AddCandidate;
