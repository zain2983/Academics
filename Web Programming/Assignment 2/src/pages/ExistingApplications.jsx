const ExistingApplications = () => {
    const candidates = useSelector((state) => state.candidates);
    const [search, setSearch] = useState("");
    const [sortBy, setSortBy] = useState("name");
    const [sortOrder, setSortOrder] = useState("asc");
  
    const filtered = candidates.filter((c) => {
      const query = search.toLowerCase();
      return (
        c.name.toLowerCase().includes(query) ||
        c.appliedFor.toLowerCase().includes(query) ||
        c.skills.some((s) => s.toLowerCase().includes(query))
      );
    });
  
    const sorted = [...filtered].sort((a, b) => {
      let valA, valB;
  
      if (sortBy === "name") {
        valA = a.name.toLowerCase();
        valB = b.name.toLowerCase();
      } else if (sortBy === "role") {
        valA = a.appliedFor.toLowerCase();
        valB = b.appliedFor.toLowerCase();
      } else if (sortBy === "skills") {
        valA = a.skills.length;
        valB = b.skills.length;
      }
  
      if (valA < valB) return sortOrder === "asc" ? -1 : 1;
      if (valA > valB) return sortOrder === "asc" ? 1 : -1;
      return 0;
    });
  
    return (
      <div className="p-4">
        <input
          type="text"
          placeholder="Search"
          value={search}
          onChange={(e) => setSearch(e.target.value)}
          className="p-2 w-full border mb-4"
        />
        <div className="flex gap-4 mb-4">
          <select
            value={sortBy}
            onChange={(e) => setSortBy(e.target.value)}
            className="p-2 border"
          >
            <option value="name">Sort by Name</option>
            <option value="role">Sort by Role</option>
            <option value="skills">Sort by Number of Skills</option>
          </select>
          <select
            value={sortOrder}
            onChange={(e) => setSortOrder(e.target.value)}
            className="p-2 border"
          >
            <option value="asc">Ascending</option>
            <option value="desc">Descending</option>
          </select>
        </div>
        {sorted.map((c) => (
          <div key={c.id} className="p-4 border mb-2 rounded shadow">
            <h3 className="text-lg font-semibold">{c.name}</h3>
            <p>{c.appliedFor}</p>
            <p>Skills: {c.skills.join(", ")}</p>
          </div>
        ))}
      </div>
    );
  };
  