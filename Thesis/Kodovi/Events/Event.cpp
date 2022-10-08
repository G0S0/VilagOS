class VOS_API Event
{
	friend class EventDispatcher;

public:
	virtual EventType GetEventType() const = 0;
	virtual const char *GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToPrint() const { return GetName(); }

	inline bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}

	bool m_Handled = false;
};
