class funny
{
public:
    int i;
    funny();
    ~funny();

    int GetSomething() const;
    void SetHidden(int newValue);
    int DoSomething() const;

private:
    int j;
};