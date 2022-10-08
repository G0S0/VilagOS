int main(int argc, char **argv)
{
	Log::Init();

	auto App = CreateApplication();
	App->run();
	delete App;
}
